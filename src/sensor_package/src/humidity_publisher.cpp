#include <random>
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class HumidityPublisher : public rclcpp::Node
{
public:
    HumidityPublisher() : Node("humidity_publisher"), use_random_(true)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>("humidity", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&HumidityPublisher::timer_callback, this));
    }

private:
    float read_humidity()
    {
        if (use_random_)
        {
            return generate_random_humidity();
        }

        // Mock reading from DHT11. Replace with actual sensor reading code.
        float humidity = 50.0;  // Replace this with actual humidity reading code
        return humidity;
    }

    float generate_random_humidity()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(30.0, 60.0);
        return dis(gen);
    }

    void timer_callback()
    {
        auto message = std_msgs::msg::Float32();
        message.data = read_humidity();
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    bool use_random_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HumidityPublisher>());
    rclcpp::shutdown();
    return 0;
}
