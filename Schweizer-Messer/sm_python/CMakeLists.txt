cmake_minimum_required(VERSION 3.16)
project(sm_python)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(Eigen3 REQUIRED)
find_package(python_module REQUIRED)
find_package(sm_common REQUIRED)
find_package(numpy_eigen REQUIRED)
find_package(sm_kinematics REQUIRED)
find_package(sm_timing REQUIRED)
find_package(sm_logging REQUIRED)
find_package(sm_matrix_archive REQUIRED)
find_package(sm_property_tree REQUIRED)

add_definitions(-D__STRICT_ANSI__)

# Set up the python exports.
set(PY_PROJECT_NAME sm_python)
set(PY_PACKAGE_DIR python/sm)

##############
## Building ##
##############

add_python_export_library(${PY_PROJECT_NAME} ${PY_PACKAGE_DIR}
  src/module.cpp
  src/export_rotational_kinematics.cpp
  src/export_rotations.cpp
  src/export_transformations.cpp
  src/export_quaternion_algebra.cpp
  src/export_homogeneous.cpp
  src/exportTransformation.cpp
  src/exportHomogeneousPoint.cpp
  src/exportTimestampCorrector.cpp
  src/exportPropertyTree.cpp
  src/exportEigen.cpp
  src/exportUncertainVector.cpp
  src/exportMatrixArchive.cpp
  src/export_kinematics_property_tree.cpp
  src/export_eigen_property_tree.cpp
  src/Logging.cpp
  src/exportNsecTime.cpp
  src/random.cpp
)

target_include_directories(${PY_PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${EIGEN3_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../numpy_eigen/include
)

target_link_libraries(${PY_PROJECT_NAME}
  PUBLIC
    sm_common::sm_common
    numpy_eigen::numpy_eigen
    sm_kinematics::sm_kinematics
    sm_timing::sm_timing
    sm_logging::sm_logging
    sm_matrix_archive::sm_matrix_archive
    sm_property_tree::sm_property_tree
    Boost::system
    Boost::serialization
)

##################
## Installation ##
##################

install(DIRECTORY include/
  DESTINATION include
)

ament_export_include_directories(include)
ament_export_dependencies(sm_common numpy_eigen sm_kinematics sm_timing sm_logging sm_matrix_archive sm_property_tree Boost Eigen3)

ament_package()
