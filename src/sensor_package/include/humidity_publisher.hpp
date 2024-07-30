/**
 * @file humidity_publisher.hpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief Header file for the HumidityPublisher class
 * @version 0.1
 * @date 2024-07-29
 * @details This file contains the declaration of the HumidityPublisher class
 * @copyright Copyright Sofiatech(c) 2024
 */

#ifndef HUMIDITY_PUBLISHER_HPP_
#define HUMIDITY_PUBLISHER_HPP_

#include <random>
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

/**
 * @class HumidityPublisher
 * @brief A ROS 2 node that publishes humidity data
 */
class HumidityPublisher : public rclcpp::Node
{
public:
    /**
     * @brief new Humidity Publisher object
     * 
     * @details initializes the node and sets up the publisher and timer
     */
    HumidityPublisher();

private:
    /**
     * @brief Read the humidity value
     * 
     * @return float The current humidity value
     */
    float read_humidity();

    /**
     * @brief Generates a random humidity value
     * 
     * @return float A random humidity value between 30.0 and 60.0
     */
    float generate_random_humidity();

    /**
     * @brief Callback function for the timer
     * 
     * This function is called at regular intervals by the timer. It reads the
     * humidity value and publishes it to the "humidity" topic.
     */
    void timer_callback();

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_; 
    rclcpp::TimerBase::SharedPtr timer_; 
    bool use_random_; 
};

#endif 
