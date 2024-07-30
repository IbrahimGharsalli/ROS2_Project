/**
 * @file temperature_publisher.cpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief Publishes temperature data
 * @version 0.1
 * @date 2024-07-29
 * 
 * @details This file contains the implementation of the TemperaturePublisher class,
 * which publishes temperature data read from an I2C device or generates random temperature values
 * 
 * @copyright Copyright Sofiatech(c) 2024
 * 
 * @note This implementation generates random temperature values between 20.0 and 30.0 if I2C communication fails
 */

#include "temperature_publisher.hpp"

TemperaturePublisher::TemperaturePublisher() : Node("temperature_publisher"), i2c_fd_(-1), use_random_(true)
{
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("temperature", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&TemperaturePublisher::timer_callback, this));
    init_i2c();
}

TemperaturePublisher::~TemperaturePublisher()
{
    if (i2c_fd_ != -1)
    {
        close(i2c_fd_);
    }
}

void TemperaturePublisher::init_i2c()
{
    const char *device = "/dev/i2c-1"; 
    const int addr = 0x48;             

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

float TemperaturePublisher::read_temperature()
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

float TemperaturePublisher::generate_random_temperature()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(20.0, 30.0);
    return dis(gen);
}

void TemperaturePublisher::timer_callback()
{
    auto message = std_msgs::msg::Float32();
    message.data = read_temperature();
    RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
    publisher_->publish(message);
}

/**
 * @brief Main function for the TemperaturePublisher node.
 * 
 * This function initializes the ROS 2 system, creates the TemperaturePublisher node,
 * and starts spinning the node to process callbacks.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit 
 */
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TemperaturePublisher>());
    rclcpp::shutdown();
    return 0;
}
