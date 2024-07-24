#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class SensorSubscriber : public rclcpp::Node
{
public:
    SensorSubscriber() : Node("sensor_subscriber")
    {
        // Subscribe to temperature topic
        temperature_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "temperature", 10, std::bind(&SensorSubscriber::temperature_callback, this, std::placeholders::_1));

        // Subscribe to humidity topic
        humidity_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "humidity", 10, std::bind(&SensorSubscriber::humidity_callback, this, std::placeholders::_1));

        // Subscribe to pressure topic
        pressure_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "pressure", 10, std::bind(&SensorSubscriber::pressure_callback, this, std::placeholders::_1));
    }

private:
    void temperature_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received temperature: '%.2f'", msg->data);
        // Add your processing or use of temperature data here
    }

    void humidity_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received humidity: '%.2f'", msg->data);
        // Add your processing or use of humidity data here
    }

    void pressure_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received pressure: '%.2f'", msg->data);
        // Add your processing or use of pressure data here
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr temperature_subscription_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr humidity_subscription_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr pressure_subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSubscriber>());
    rclcpp::shutdown();
    return 0;
}
