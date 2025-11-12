cmake_minimum_required(VERSION 3.16)
project(sm_opencv)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(sm_common REQUIRED)
find_package(OpenCV REQUIRED)

add_definitions(-D__STRICT_ANSI__)

# Create an interface library for header-only content
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} INTERFACE
  sm_common::sm_common
)

install(DIRECTORY include/
  DESTINATION include
)

# Export interface library targets
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
)

ament_export_targets(${PROJECT_NAME}Targets)
ament_export_include_directories(include)
ament_export_dependencies(sm_common)

ament_package()
