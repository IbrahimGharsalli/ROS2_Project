/**
 * @file sensor_subscriber.cpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief This is the implementation file for the SensorSubscriber class
 * @version 0.1
 * @date 2024-07-28
 * @details Contains the ROS 2 node for subscribing to sensor data
 * @copyright Copyright Sofiatech(c) 2024
 */

#include "sensor_subscriber.hpp"

/**
 * @brief new Sensor Subscriber object
 */
SensorSubscriber::SensorSubscriber() : Node("sensor_subscriber")
{
    temperature_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
        "temperature", 10, std::bind(&SensorSubscriber::temperature_callback, this, std::placeholders::_1));

    humidity_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
        "humidity", 10, std::bind(&SensorSubscriber::humidity_callback, this, std::placeholders::_1));

    pressure_subscription_ = this->create_subscription<std_msgs::msg::Float32>(
        "pressure", 10, std::bind(&SensorSubscriber::pressure_callback, this, std::placeholders::_1));
}

/**
 * @brief Callback function for the temperature subscription
 * @param msg Shared pointer to the received temperature message
 */
void SensorSubscriber::temperature_callback(const std_msgs::msg::Float32::SharedPtr msg)
{
    if (msg == nullptr) {
        RCLCPP_ERROR(this->get_logger(), "Received null temperature message");
        return;
    }

    try {
        RCLCPP_INFO(this->get_logger(), "Received temperature: '%.2f'", msg->data);
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Error processing temperature message: %s", e.what());
    }
}

/**
 * @brief Callback function for the humidity subscription
 * @param msg Shared pointer to the received humidity message
 */
void SensorSubscriber::humidity_callback(const std_msgs::msg::Float32::SharedPtr msg)
{
    if (msg == nullptr) {
        RCLCPP_ERROR(this->get_logger(), "Received null humidity message");
        return;
    }

    try {
        RCLCPP_INFO(this->get_logger(), "Received humidity: '%.2f'", msg->data);
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Error processing humidity message: %s", e.what());
    }
}

/**
 * @brief Callback function for the pressure subscription
 * @param msg Shared pointer to the received pressure message
 */
void SensorSubscriber::pressure_callback(const std_msgs::msg::Float32::SharedPtr msg)
{
    if (msg == nullptr) {
        RCLCPP_ERROR(this->get_logger(), "Received null pressure message");
        return;
    }

    try {
        RCLCPP_INFO(this->get_logger(), "Received pressure: '%.2f'", msg->data);
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Error processing pressure message: %s", e.what());
    }
}

/**
 * @brief Main function for the SensorSubscriber node
 * @param argc Argument count
 * @param argv Argument vector
 * @return int exit
 */
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSubscriber>());
    rclcpp::shutdown();
    return 0;
}
