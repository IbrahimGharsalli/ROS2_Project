from setuptools import find_packages, setup

package_name = 'plot_sensor_data'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/plot_launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='cyber',
    maintainer_email='gharsalli.ibrahim@gmail.com',
    description='Package to plot sensor data (temperature, humidity, and pressure).',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'plot_node = plot_sensor_data.plot_node:main',
        ],
    },
)
