/**
 * @file pressure_publisher.hpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief Header file for the PressurePublisher class
 * @version 0.1
 * @date 2024-07-29
 * @details This file contains the declaration of the PressurePublisher class
 * @copyright Copyright Sofiatech(c) 2024
 */

#ifndef PRESSURE_PUBLISHER_HPP_
#define PRESSURE_PUBLISHER_HPP_

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

/**
 * @class PressurePublisher
 * @brief ROS 2 node that publishes pressure data
 */
class PressurePublisher : public rclcpp::Node
{
public:
    /**
     * @brief new Pressure Publisher object.
     * 
     * @details initializes the node, sets up the publisher and timer 
     * and initializes the SPI communication
     */
    PressurePublisher();

    /**
     * @brief Destroy the Pressure Publisher object
     */
    ~PressurePublisher();

private:
    /**
     * @brief Initialize the SPI communication
     * 
     * @details This function sets up the SPI device parameters such as mode, bits per word,
     * and speed. If the initialization fails, the node switches to using random
     * pressure values
     */
    void init_spi();

    /**
     * @brief Reads the pressure value
     * 
     * @return float The current pressure value
     */
    float read_pressure();

    /**
     * @brief Generates a random pressure value
     * 
     * @return float A random pressure value between 900.0 and 1100.0
     */
    float generate_random_pressure();

    /**
     * @brief Callback function for the timer.
     * 
     * @details This function is called at regular intervals by the timer. It reads the
     * pressure value and publishes it to the "pressure" topic.
     */
    void timer_callback();

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;  
    rclcpp::TimerBase::SharedPtr timer_; 
    int spi_fd_; 
    bool use_random_; 
};

#endif 
