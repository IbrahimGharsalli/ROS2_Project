/**
 * @file humidity_publisher.cpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief Publishes humidity data
 * @version 0.1
 * @date 2024-07-29
 * @details This file contains the implementation of the HumidityPublisher class,
 * which publishes random humidity data.
 * @copyright Copyright Sofiatech(c) 2024
 * @note This implementation generates random humidity values between 30.0 and 60.0.
 */

#include "humidity_publisher.hpp"

HumidityPublisher::HumidityPublisher() : Node("humidity_publisher"), use_random_(true)
{
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("humidity", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&HumidityPublisher::timer_callback, this));
}

float HumidityPublisher::read_humidity()
{
    if (use_random_)
    {
        return generate_random_humidity();
    }

    
    float humidity = 50.0;  
    return humidity;
}

float HumidityPublisher::generate_random_humidity()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(30.0, 60.0);
    return dis(gen);
}

void HumidityPublisher::timer_callback()
{
    auto message = std_msgs::msg::Float32();
    message.data = read_humidity();
    RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
    publisher_->publish(message);
}

/**
 * @brief Main function for the HumidityPublisher node
 * 
 * This function initializes the ROS 2 system, creates the HumidityPublisher node,
 * and starts spinning the node to process callbacks
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return int Exit 
 */
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HumidityPublisher>());
    rclcpp::shutdown();
    return 0;
}
