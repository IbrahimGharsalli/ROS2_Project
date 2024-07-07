import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import matplotlib.pyplot as plt
from collections import deque

class TemperaturePlotter(Node):
    def __init__(self):
        super().__init__('temperature_plotter')
        self.subscription = self.create_subscription(
            Float32,
            'temperature',
            self.listener_callback,
            10)
        self.subscription  
        self.temperatures = deque(maxlen=100)
        plt.ion()
        self.fig, self.ax = plt.subplots()
        self.line, = self.ax.plot([], [], 'r-')
        self.ax.set_ylim(15, 35)
        self.ax.set_xlim(0, 100)
        plt.show()

    def listener_callback(self, msg):
        self.temperatures.append(msg.data)
        self.line.set_xdata(range(len(self.temperatures)))
        self.line.set_ydata(self.temperatures)
        self.ax.draw_artist(self.ax.patch)
        self.ax.draw_artist(self.line)
        self.fig.canvas.flush_events()
        self.get_logger().info('Received: "%f"' % msg.data)

def main(args=None):
    rclpy.init(args=args)
    node = TemperaturePlotter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
