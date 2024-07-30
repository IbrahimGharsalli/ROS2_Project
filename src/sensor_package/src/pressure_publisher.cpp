/**
 * @file pressure_publisher.cpp
 * @author Ibrahim Gharsalli (gharsalli.ibrahim@gmail.com)
 * @brief Publishes pressure data
 * @version 0.1
 * @date 2024-07-29
 * @details This file contains the implementation of the PressurePublisher class,
 * which publishes pressure data read from an SPI device or generates random pressure values
 * 
 * @copyright Copyright Sofiatech(c) 2024
 * @note This implementation generates random pressure values between 900.0 and 1100.0 if SPI communication fails.
 */

#include "pressure_publisher.hpp"

PressurePublisher::PressurePublisher() : Node("pressure_publisher"), spi_fd_(-1), use_random_(true)
{
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("pressure", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&PressurePublisher::timer_callback, this));
    init_spi();
}

PressurePublisher::~PressurePublisher()
{
    if (spi_fd_ != -1)
    {
        close(spi_fd_);
    }
}

void PressurePublisher::init_spi()
{
    const char *device = "/dev/spidev0.0"; 
    const uint8_t mode = SPI_MODE_0;
    const uint8_t bits_per_word = 8;
    const uint32_t speed = 1000000; 

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

float PressurePublisher::read_pressure()
{
    if (use_random_)
    {
        return generate_random_pressure();
    }

  
    return 1000.0; 
}

float PressurePublisher::generate_random_pressure()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(900.0, 1100.0); // Example pressure range
    return dis(gen);
}

void PressurePublisher::timer_callback()
{
    auto message = std_msgs::msg::Float32();
    message.data = read_pressure();
    RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
    publisher_->publish(message);
}

/**
 * @brief Main function for the PressurePublisher node.
 * 
 * This function initializes the ROS 2 system, creates the PressurePublisher node,
 * and starts spinning the node to process callbacks
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return int Exit
 */
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PressurePublisher>());
    rclcpp::shutdown();
    return 0;
}
