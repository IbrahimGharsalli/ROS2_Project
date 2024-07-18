from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    sensor_package_dir = get_package_share_directory('sensor_package')
    data_processor_dir = get_package_share_directory('data_processor')

    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([sensor_package_dir, '/launch/sensor_launch.py'])
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([data_processor_dir, '/launch/data_launch.py'])
        ),
    ])

