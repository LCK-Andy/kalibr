cmake_minimum_required(VERSION 3.16)
project(aslam_imgproc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(sm_common REQUIRED)
find_package(sm_eigen REQUIRED)
find_package(sm_random REQUIRED)
find_package(sm_boost REQUIRED)
find_package(sm_kinematics REQUIRED)
find_package(sm_opencv REQUIRED)
find_package(sm_logging REQUIRED)
find_package(sm_property_tree REQUIRED)
find_package(aslam_time REQUIRED)
find_package(aslam_cameras REQUIRED)
find_package(opencv2_catkin REQUIRED)
find_package(numpy_eigen REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

add_library(${PROJECT_NAME} 
  src/UndistorterBase.cpp
  src/calculateOverlappingFov.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(${PROJECT_NAME} PUBLIC -Wno-deprecated-copy -Wno-maybe-uninitialized)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Boost::system
    sm_common::sm_common
    sm_eigen::sm_eigen
    sm_random::sm_random
    sm_boost::sm_boost
    sm_kinematics::sm_kinematics
    sm_opencv::sm_opencv
    sm_logging::sm_logging
    sm_property_tree::sm_property_tree
    aslam_time::aslam_time
    aslam_cameras::aslam_cameras
    numpy_eigen::numpy_eigen
)

##################
## Installation ##
##################

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include
)

ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)
ament_export_include_directories(include)
ament_export_dependencies(sm_common sm_eigen sm_random sm_boost sm_kinematics sm_opencv sm_logging sm_property_tree aslam_time aslam_cameras numpy_eigen Boost Eigen3)

ament_package()
