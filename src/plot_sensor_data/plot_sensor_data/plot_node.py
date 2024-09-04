# ~/ros2_ws/src/plot_sensor_data/plot_sensor_data/plot_node.py
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import matplotlib.pyplot as plt
from collections import deque
from datetime import datetime, timedelta

class SensorPlotter(Node):
    def __init__(self):
        super().__init__('sensor_plotter')
        
        # Subscriptions
        self.temperature_subscription = self.create_subscription(
            Float32, 'temperature', self.temperature_callback, 10)
        self.humidity_subscription = self.create_subscription(
            Float32, 'humidity', self.humidity_callback, 10)
        self.pressure_subscription = self.create_subscription(
            Float32, 'pressure', self.pressure_callback, 10)

        # Data storage
        self.temperature_data = []
        self.humidity_data = []
        self.pressure_data = []
        self.temperature_averages = deque(maxlen=100)
        self.humidity_averages = deque(maxlen=100)
        self.pressure_averages = deque(maxlen=100)

        # Time tracking
        self.last_average_time = datetime.now()

        # Matplotlib setup
        plt.ion()
        self.fig, self.ax = plt.subplots(3, 1, figsize=(10, 8))

        # Temperature plot
        self.temperature_line, = self.ax[0].plot([], [], 'r-', label='Temperature Avg')
        self.ax[0].set_ylim(15, 35)
        self.ax[0].set_xlim(0, 100)
        self.ax[0].legend()
        
        # Humidity plot
        self.humidity_line, = self.ax[1].plot([], [], 'b-', label='Humidity Avg')
        self.ax[1].set_ylim(20, 80)
        self.ax[1].set_xlim(0, 100)
        self.ax[1].legend()

        # Pressure plot
        self.pressure_line, = self.ax[2].plot([], [], 'g-', label='Pressure Avg')
        self.ax[2].set_ylim(900, 1100)
        self.ax[2].set_xlim(0, 100)
        self.ax[2].legend()

        plt.tight_layout()
        plt.show()

    def temperature_callback(self, msg):
        self.temperature_data.append(msg.data)
        self.update_plot()

    def humidity_callback(self, msg):
        self.humidity_data.append(msg.data)
        self.update_plot()

    def pressure_callback(self, msg):
        self.pressure_data.append(msg.data)
        self.update_plot()

    def update_plot(self):
        current_time = datetime.now()

        if current_time - self.last_average_time >= timedelta(seconds=5):
            # Calculate averages
            if self.temperature_data:
                temperature_avg = sum(self.temperature_data) / len(self.temperature_data)
                self.temperature_averages.append(temperature_avg)
                self.temperature_data = []
                self.get_logger().info(f'Average temperature: {temperature_avg:.2f}')

            if self.humidity_data:
                humidity_avg = sum(self.humidity_data) / len(self.humidity_data)
                self.humidity_averages.append(humidity_avg)
                self.humidity_data = []
                self.get_logger().info(f'Average humidity: {humidity_avg:.2f}')

            if self.pressure_data:
                pressure_avg = sum(self.pressure_data) / len(self.pressure_data)
                self.pressure_averages.append(pressure_avg)
                self.pressure_data = []
                self.get_logger().info(f'Average pressure: {pressure_avg:.2f}')

            self.last_average_time = current_time

            # Update plot data
            self.temperature_line.set_xdata(range(len(self.temperature_averages)))
            self.temperature_line.set_ydata(self.temperature_averages)
            self.humidity_line.set_xdata(range(len(self.humidity_averages)))
            self.humidity_line.set_ydata(self.humidity_averages)
            self.pressure_line.set_xdata(range(len(self.pressure_averages)))
            self.pressure_line.set_ydata(self.pressure_averages)

            # Redraw plots
            for ax in self.ax:
                ax.draw_artist(ax.patch)
                ax.draw_artist(self.temperature_line)
                ax.draw_artist(self.humidity_line)
                ax.draw_artist(self.pressure_line)
            self.fig.canvas.flush_events()

def main(args=None):
    rclpy.init(args=args)
    node = SensorPlotter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
