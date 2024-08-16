# ROS2_Project

Simple ros2 data centralisation from sensors for a robot navigation purpose.

## Features

- **Publisher:** Implemented in C++ for three different sensors.
- **Subscriber:** Implemented in Python to facilitate data visualization using matplotlib.
- **Dashboard:** A user-friendly dashboard is implemented using an HTML file to display sensor data.

## Environment

Ubuntu 20.04 (on Windows11 wsl2)  
ROS2 humble
## Diagram 

<img src="https://github.com/user-attachments/assets/c648d7f2-1a3c-4691-8bb6-bfc578988d84" alt="drawing" width="720"/>  

## File Structure

```plaintext
ros2_ws/
├── src/
│   ├── plot_sensor_data/
│   │   ├── launch/
│   │   │   └── plot_launch.py
│   │   ├── plot_sensor_data/
│   │   │   ├── __init__.py
│   │   │   └── plot_node.py
│   │   ├── package.xml
│   │   └── setup.py
│   ├── sensor_package/
│   │   ├── src/
│   │   │   ├── temperature_publisher.cpp
│   │   │   ├── humidity_publisher.cpp
│   │   │   └── pressure_publisher.cpp
│   │   ├── include/
│   │   │   └── sensor_package/
│   │   ├── launch/
│   │   │   └── sensor_launch.py
│   │   ├── package.xml
│   │   └── CMakeLists.txt
│   ├── rosbridge_server_launch/
│   │   ├── launch/
│   │   │   └── rosbridge_server_launch.py
│   │   ├── package.xml
│   │   └── CMakeLists.txt
│   ├── sensor_subscriber/
│   │   ├── src/
│   │   │   └── sensor_subscriber.cpp
│   │   ├── launch/
│   │   │   └── subscriber_launch.py
│   │   ├── package.xml
│   │   └── CMakeLists.txt
│   └── dashboard/
│       └── index.html
├── install/
├── build/
└── log/
```
## Package
- **plot_sensor_data:**
  * Publishes sensor data to ROS 2 topics and plots it using Matplotlib.
- **sensor_package:**
  * Contains nodes for publishing temperature, humidity, and pressure sensor data.
- **rosbridge_server_launch:**
  * Launches rosbridge_server for WebSocket communication with ROS 2.
- **sensor_subscriber:**
  * Contains a subscriber node to subscribe to the sensor topics.
- **Dashboard:**
  * A web-based dashboard for visualizing sensor data in real-time.

## Dependencies
  * ROS 2 (Humble or later)
  * rosbridge_suite
  * Python 3
  * Matplotlib
  * Chart.js (for the web dashboard)
  
## Build

Clone project into src of ros2 workspace 
```bash
cd {ros2_ws}/src
git clone https://github.com/IbrahimGharsalli/ROS2_Project.git
```
Go back to ros2 workspace and build
```bash
cd {ros2_ws}
colcon build
```
Source the workspace
```bash
source install/setup.bash
```
## Run

### Publisher
- **Temperature:**
   ```bash
   ros2 run sensor_package temperature_publisher
   ```
<img src="https://github.com/user-attachments/assets/a106d31d-2bdf-41c0-9bd5-90cd21701d31" alt="drawing" width="480"/>   

- **Humidity:**
   ```bash
   ros2 run sensor_package humidity_publisher
   ```
<img src="https://github.com/user-attachments/assets/33fdec01-b5f2-4459-94ff-9c5dedcae242" alt="drawing" width="480"/>  

- **Pressure:**
   ```bash
   ros2 run sensor_package pressure_publisher
   ```
<img src="https://github.com/user-attachments/assets/8934eb05-b83c-41e7-ab6a-147abc977a43" alt="drawing" width="480"/>   


- **Launch the sensor nodes:**
   ```bash
   ros2 launch sensor_package sensor_launch.py
   ```

### Subscriber
 ```bash
 ros2 run data_processor sensor_subscriber
 ```
 or
 ```bash
 ros2 launch data_processor data_launch.py
 ```
<img src="https://github.com/user-attachments/assets/94d486f6-8b2a-46ff-93a3-37be090100e0" alt="drawing" width="480"/>  


### Publisher & Subscriber
 ```bash
 ros2 launch main_launch.py
 ```
## Plot
 ```bash
 ros2 launch plot_sensor_data plot_launch.py
 ```
## Rosbridge_server
 ```bash
 ros2 launch rosbridge_server_launch rosbridge_server_launch.py
 ```
## Web Dashboard
1. Navigate to the directory containing index.html:
   ```bash
   cd src/dashboard
   ```
3. Serve the index.html file using a simple HTTP server (Python 3):
   ```bash
   python3 -m http.server 8000
   ```
5. Open a web browser and navigate to:
   http://localhost:8000/index.html

   
<img src="https://github.com/user-attachments/assets/6251ddad-181a-4a86-8716-9161893ac058" alt="drawing" width="720"/> 



You should now see real-time plots for temperature, humidity, and pressure data on the dashboard.





   
      
      
    
    
  







