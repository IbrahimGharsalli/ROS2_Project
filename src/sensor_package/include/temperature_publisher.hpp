/**
 * @file temperature_publisher.hpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief Header file for the TemperaturePublisher class
 * @version 0.1
 * @date 2024-07-29
 * @details This file contains the declaration of the TemperaturePublisher class,
 * which publishes temperature data read from an I2C device.
 * @copyright Copyright Sofiatech(c) 2024
 */

#ifndef TEMPERATURE_PUBLISHER_HPP_
#define TEMPERATURE_PUBLISHER_HPP_

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

/**
 * @class TemperaturePublisher
 * @brief A ROS 2 node that publishes temperature data
 */
class TemperaturePublisher : public rclcpp::Node
{
public:
    /**
     * @brief Construct a new Temperature Publisher object.
     * 
     * @details initializes the node, sets up the publisher and timer,
     * and initializes the I2C communication.
     */
    TemperaturePublisher();

    /**
     * @brief Destroy the Temperature Publisher object.
     */
    ~TemperaturePublisher();

private:
    /**
     * @brief Initialize the I2C communication.
     * 
     * This function sets up the I2C device parameters. If the initialization fails,
     * the node switches to using random temperature values.
     */
    void init_i2c();

    /**
     * @brief Reads the temperature value.
     * 
     * @return float The current temperature value.
     */
    float read_temperature();

    /**
     * @brief Generates a random temperature value.
     * 
     * @return float A random temperature value between 20.0 and 30.0.
     */
    float generate_random_temperature();

    /**
     * @brief Callback function for the timer.
     * 
     * This function is called at regular intervals by the timer. It reads the
     * temperature value and publishes it to the "temperature" topic.
     */
    void timer_callback();

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_; 
    rclcpp::TimerBase::SharedPtr timer_;
    int i2c_fd_; 
    bool use_random_; 
};

#endif 
