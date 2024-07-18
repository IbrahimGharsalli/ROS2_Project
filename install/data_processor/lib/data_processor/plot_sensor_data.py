import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Temperature, FluidPressure, RelativeHumidity
import matplotlib.pyplot as plt

class SensorPlotter(Node):
    def __init__(self):
        super().__init__('sensor_plotter')
        self.temperature_subscription = self.create_subscription(
            Temperature,
            'temperature',
            self.temperature_callback,
            10)
        self.pressure_subscription = self.create_subscription(
            FluidPressure,
            'pressure',
            self.pressure_callback,
            10)
        self.humidity_subscription = self.create_subscription(
            RelativeHumidity,
            'humidity',
            self.humidity_callback,
            10)
        self.temperatures = []
        self.pressures = []
        self.humidities = []

    def temperature_callback(self, msg):
        self.get_logger().info(f'Received temperature: {msg.temperature}')
        self.temperatures.append(msg.temperature)
        self.plot_data()

    def pressure_callback(self, msg):
        self.get_logger().info(f'Received pressure: {msg.fluid_pressure}')
        self.pressures.append(msg.fluid_pressure)
        self.plot_data()

    def humidity_callback(self, msg):
        self.get_logger().info(f'Received humidity: {msg.relative_humidity}')
        self.humidities.append(msg.relative_humidity)
        self.plot_data()

    def plot_data(self):
        plt.clf()
        plt.subplot(3, 1, 1)
        plt.plot(self.temperatures, label='Temperature (C)')
        plt.legend()
        plt.subplot(3, 1, 2)
        plt.plot(self.pressures, label='Pressure (hPa)')
        plt.legend()
        plt.subplot(3, 1, 3)
        plt.plot(self.humidities, label='Humidity (%)')
        plt.legend()
        plt.pause(0.1)

def main(args=None):
    rclpy.init(args=args)
    node = SensorPlotter()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
        plt.close()

if __name__ == '__main__':
    main()