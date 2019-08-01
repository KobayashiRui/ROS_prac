cmake_minimum_required(VERSION 3.5)
project(test_gazebo)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # we dont use add_compile_options with pedantic in message packages
  # because the Python C extensions dont comply with it
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

find_package(gazebo_dev REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(gazebo_test SHARED gazebo_ros_template.cpp)

include_directories(${gazebo_dev_INCLUDE_DIRS})
include_directories(${gazebo_msgs_INCLUDE_DIRS})
include_directories(${gazebo_ros_INCLUDE_DIRS})
include_directories(${rclcpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})

target_link_libraries(gazebo_test ${gazebo_dev_LIBRARIES})
target_link_libraries(gazebo_test ${gazebo_msgs_LIBRARIES})
target_link_libraries(gazebo_test ${gazebo_ros_LIBRARIES})
target_link_libraries(gazebo_test ${rclcpp_LIBRARIES})
target_link_libraries(gazebo_test ${std_msgs_LIBRARIES})
target_link_libraries(gazebo_test ${GAZEBO_LIBRARIES})