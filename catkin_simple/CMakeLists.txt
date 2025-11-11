cmake_minimum_required(VERSION 3.16)
project(catkin_simple)

find_package(ament_cmake REQUIRED)

ament_package(
  CONFIG_EXTRAS cmake/catkin_simple-extras.cmake.em
)
