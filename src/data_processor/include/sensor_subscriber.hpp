/**
 * @file sensor_subscriber.hpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief This is the header file for the SensorSubscriber class
 * @version 0.1
 * @date 2024-07-28
 * @details Contains the class definition for the ROS 2 node that subscribes to sensor data
 * @copyright Copyright Sofiatech(c) 2024
 */

#ifndef SENSOR_SUBSCRIBER_HPP
#define SENSOR_SUBSCRIBER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

/**
 * @class SensorSubscriber
 * @brief A ROS 2 node that subscribes to temperature, humidity, and pressure sensor topics
 */
class SensorSubscriber : public rclcpp::Node
{
public:
    /**
     * @brief Construct a new Sensor Subscriber object
     */
    SensorSubscriber();

private:
    /**
     * @brief Callback function for the temperature subscription
     * @param msg Shared pointer to the received temperature message
     */
    void temperature_callback(const std_msgs::msg::Float32::SharedPtr msg);

    /**
     * @brief Callback function for the humidity subscription
     * @param msg Shared pointer to the received humidity message
     */
    void humidity_callback(const std_msgs::msg::Float32::SharedPtr msg);

    /**
     * @brief Callback function for the pressure subscription
     * @param msg Shared pointer to the received pressure message
     */
    void pressure_callback(const std_msgs::msg::Float32::SharedPtr msg);

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr temperature_subscription_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr humidity_subscription_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr pressure_subscription_;
};

#endif 
