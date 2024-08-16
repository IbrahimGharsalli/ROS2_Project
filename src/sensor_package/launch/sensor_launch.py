from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='sensor_package',
            executable='temperature_publisher',
            name='temperature_publisher',
            output='screen'
        ),
        Node(
            package='sensor_package',
            executable='pressure_publisher',
            name='pressure_publisher',
            output='screen'
        ),
        Node(
            package='sensor_package',
            executable='humidity_publisher',
            name='humidity_publisher',
            output='screen'
        ),
    ])
