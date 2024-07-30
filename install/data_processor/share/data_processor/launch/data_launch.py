from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='data_processor',
            executable='sensor_subscriber',
            name='sensor_subscriber',
            output='screen'
        ),
    ])
