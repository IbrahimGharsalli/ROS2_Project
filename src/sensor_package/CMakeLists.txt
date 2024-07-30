cmake_minimum_required(VERSION 3.8)
project(sensor_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(temperature_publisher src/temperature_publisher.cpp)
add_executable(pressure_publisher src/pressure_publisher.cpp)
add_executable(humidity_publisher src/humidity_publisher.cpp)

ament_target_dependencies(temperature_publisher rclcpp sensor_msgs)
ament_target_dependencies(pressure_publisher rclcpp sensor_msgs)
ament_target_dependencies(humidity_publisher rclcpp sensor_msgs)

include_directories(include)
install(TARGETS
  temperature_publisher
  pressure_publisher
  humidity_publisher
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)
  
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
