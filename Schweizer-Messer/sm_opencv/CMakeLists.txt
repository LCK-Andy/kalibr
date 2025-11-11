cmake_minimum_required(VERSION 3.16)
project(sm_opencv)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(sm_common REQUIRED)
find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(OpenCV REQUIRED)

add_definitions(-D__STRICT_ANSI__)

install(DIRECTORY include/
  DESTINATION include
)

ament_export_include_directories(include)
ament_export_dependencies(sm_common Boost OpenCV)

ament_package()
