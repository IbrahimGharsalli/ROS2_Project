// ~/ros2_ws/src/temperature_sensor/src/temperature_publisher.cpp
#include <random>
#include <chrono>
#include <memory>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class TemperaturePublisher : public rclcpp::Node
{
public:
    TemperaturePublisher() : Node("temperature_publisher"), i2c_fd_(-1), use_random_(true)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>("temperature", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&TemperaturePublisher::timer_callback, this));
        init_i2c();
    }

    ~TemperaturePublisher()
    {
        if (i2c_fd_ != -1)
        {
            close(i2c_fd_);
        }
    }

private:
    void init_i2c()
    {
        const char *device = "/dev/i2c-1"; // Adjust based on your system
        const int addr = 0x48;             // TMP102 default I2C address

        if ((i2c_fd_ = open(device, O_RDWR)) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open the i2c bus");
            use_random_ = true;
            return;
        }

        if (ioctl(i2c_fd_, I2C_SLAVE, addr) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to acquire bus access and/or talk to slave");
            use_random_ = true;
            return;
        }

        use_random_ = false;
    }

    float read_temperature()
    {
        if (use_random_)
        {
            return generate_random_temperature();
        }

        uint8_t buf[2] = {0};
        if (read(i2c_fd_, buf, 2) != 2)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to read from the i2c bus");
            return 0.0;
        }
        int temp = (buf[0] << 4) | (buf[1] >> 4);
        if (temp > 0x7FF)
        {
            temp |= 0xF000;
        }
        return temp * 0.0625;
    }

    float generate_random_temperature()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(20.0, 30.0);
        return dis(gen);
    }

    void timer_callback()
    {
        auto message = std_msgs::msg::Float32();
        message.data = read_temperature();
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int i2c_fd_;
    bool use_random_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TemperaturePublisher>());
    rclcpp::shutdown();
    return 0;
}
