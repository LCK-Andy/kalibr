cmake_minimum_required(VERSION 3.16)
project(opencv2_catkin)

find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)

# Create config file for downstream packages
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/opencv2-extras.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/opencv2-extrasConfig.cmake
  @ONLY
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/opencv2-extrasConfig.cmake
  DESTINATION share/cmake/opencv2_catkin
)

ament_export_include_directories()
ament_export_libraries()
ament_export_targets()

# Export for find_package users
set(opencv2_catkin_LIBRARY_DIRS ${OpenCV_LIB_DIR})
set(opencv2_catkin_LIBRARIES ${OpenCV_LIBS})
set(opencv2_catkin_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS})

message(STATUS "-- Using OpenCV library directory ${opencv2_catkin_LIBRARY_DIRS}")
message(STATUS "-- Found OpenCV include directory ${opencv2_catkin_INCLUDE_DIRS}")
message(STATUS "-- Found OpenCV libraries ${opencv2_catkin_LIBRARIES}")

ament_package()
