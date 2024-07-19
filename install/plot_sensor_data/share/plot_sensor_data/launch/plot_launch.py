from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='plot_sensor_data',
            executable='plot_node',
            output='screen',
            name='plot_node'
        ),
        Node(
            package='sensor_package',
            executable='temperature_publisher',
            output='screen',
            name='temperature_publisher'
        ),
        Node(
            package='sensor_package',
            executable='pressure_publisher',
            output='screen',
            name='pressure_publisher'
        ),
        Node(
            package='sensor_package',
            executable='humidity_publisher',
            output='screen',
            name='humidity_publisher'
        )
    ])
