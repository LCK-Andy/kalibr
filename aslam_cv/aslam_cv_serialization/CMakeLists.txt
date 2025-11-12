cmake_minimum_required(VERSION 3.16)
project(aslam_cv_serialization)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization system)
find_package(aslam_cameras REQUIRED)
find_package(aslam_time REQUIRED)
find_package(sm_common REQUIRED)
find_package(sm_boost REQUIRED)
find_package(sm_property_tree REQUIRED)
find_package(sm_eigen REQUIRED)
find_package(sm_kinematics REQUIRED)
find_package(sm_opencv REQUIRED)
find_package(sm_logging REQUIRED)
find_package(opencv2_catkin REQUIRED)
find_package(sm_random REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

#common commands for building c++ executables and libraries
INCLUDE(autogen_cameras.cmake)
#INCLUDE(autogen_frames.cmake)

add_library(${PROJECT_NAME}
  ${AUTOGEN_CAMERA_CPP_FILES}
  src/FrameBaseSerialization.cpp
  src/LinkCvSerialization.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    aslam_cameras::aslam_cameras
    aslam_time::aslam_time
    sm_common::sm_common
    sm_boost::sm_boost
    sm_property_tree::sm_property_tree
    sm_eigen::sm_eigen
    sm_kinematics::sm_kinematics
    sm_opencv::sm_opencv
    sm_logging::sm_logging
    sm_random::sm_random
    Boost::serialization
    Boost::system
    ${OpenCV_LIBRARIES}
    Eigen3::Eigen
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
ament_export_dependencies(aslam_cameras aslam_time sm_common sm_boost sm_property_tree sm_eigen sm_kinematics sm_opencv sm_logging sm_random Boost Eigen3)

ament_package()
