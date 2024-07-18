#include <chrono>
#include <memory>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include <random>

using namespace std::chrono_literals;

class PressurePublisher : public rclcpp::Node
{
public:
    PressurePublisher() : Node("pressure_publisher"), spi_fd_(-1), use_random_(true)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>("pressure", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&PressurePublisher::timer_callback, this));
        init_spi();
    }

    ~PressurePublisher()
    {
        if (spi_fd_ != -1)
        {
            close(spi_fd_);
        }
    }

private:
    void init_spi()
    {
        const char *device = "/dev/spidev0.0"; // Adjust based on your system and SPI bus
        const uint8_t mode = SPI_MODE_0;
        const uint8_t bits_per_word = 8;
        const uint32_t speed = 1000000; // 1 MHz speed, adjust as needed

        if ((spi_fd_ = open(device, O_RDWR)) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open the SPI bus");
            use_random_ = true;
            return;
        }

        if (ioctl(spi_fd_, SPI_IOC_WR_MODE, &mode) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to set SPI mode");
            use_random_ = true;
            return;
        }

        if (ioctl(spi_fd_, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to set SPI bits per word");
            use_random_ = true;
            return;
        }

        if (ioctl(spi_fd_, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to set SPI speed");
            use_random_ = true;
            return;
        }

        use_random_ = false;
    }

    float read_pressure()
    {
        if (use_random_)
        {
            return generate_random_pressure();
        }

        // SPI read implementation for BMP280 goes here
        // Replace with actual SPI communication with the BMP280 sensor
        // Example placeholder: read from SPI and return pressure value
        return 1000.0; // Placeholder value, replace with actual reading
    }

    float generate_random_pressure()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(900.0, 1100.0); // Example pressure range
        return dis(gen);
    }

    void timer_callback()
    {
        auto message = std_msgs::msg::Float32();
        message.data = read_pressure();
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int spi_fd_;
    bool use_random_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PressurePublisher>());
    rclcpp::shutdown();
    return 0;
}
