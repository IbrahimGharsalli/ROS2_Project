import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from collections import deque

class PlotNode(Node):
    def __init__(self):
        super().__init__('plot_node')

        self.temperature_sub = self.create_subscription(
            Float32, 'temperature', self.temperature_callback, 10)
        self.humidity_sub = self.create_subscription(
            Float32, 'humidity', self.humidity_callback, 10)
        self.pressure_sub = self.create_subscription(
            Float32, 'pressure', self.pressure_callback, 10)

        self.temperature_data = deque(maxlen=100)
        self.humidity_data = deque(maxlen=100)
        self.pressure_data = deque(maxlen=100)

        self.fig, self.ax = plt.subplots(3, 1)
        self.ani = FuncAnimation(self.fig, self.update_plot, interval=1000)

    def temperature_callback(self, msg):
        self.temperature_data.append(msg.data)
        self.get_logger().info(f'Received temperature: {msg.data}')  # Log received data

    def humidity_callback(self, msg):
        self.humidity_data.append(msg.data)
        self.get_logger().info(f'Received humidity: {msg.data}')  # Log received data

    def pressure_callback(self, msg):
        self.pressure_data.append(msg.data)
        self.get_logger().info(f'Received pressure: {msg.data}')  # Log received data

    def update_plot(self, frame):
        if not self.temperature_data:
            return

        self.ax[0].clear()
        self.ax[0].plot(list(self.temperature_data))
        self.ax[0].set_title('Temperature')
        self.ax[0].set_ylim([min(self.temperature_data, default=0) - 5, max(self.temperature_data, default=0) + 5])

        self.ax[1].clear()
        self.ax[1].plot(list(self.humidity_data))
        self.ax[1].set_title('Humidity')
        self.ax[1].set_ylim([min(self.humidity_data, default=0) - 5, max(self.humidity_data, default=0) + 5])

        self.ax[2].clear()
        self.ax[2].plot(list(self.pressure_data))
        self.ax[2].set_title('Pressure')
        self.ax[2].set_ylim([min(self.pressure_data, default=0) - 5, max(self.pressure_data, default=0) + 5])

        self.fig.tight_layout()

    def start_plotting(self):
        plt.show()

def main(args=None):
    rclpy.init(args=args)
    node = PlotNode()
    try:
        node.start_plotting()
    except KeyboardInterrupt:
        pass
    finally:
        rclpy.shutdown()

if __name__ == '__main__':
    main()
