cmake_minimum_required(VERSION 3.16)
project(bsplines)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

find_package(ament_cmake REQUIRED)
# Find external dependencies FIRST before importing targets that depend on them
find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(TBB REQUIRED)
find_package(Eigen3 REQUIRED)

find_package(sm_common REQUIRED)
find_package(sm_timing REQUIRED)
find_package(sm_eigen REQUIRED)
find_package(sm_kinematics REQUIRED)
find_package(sparse_block_matrix REQUIRED)

add_library(${PROJECT_NAME} 
  src/BSpline.cpp
  src/BSplinePose.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    sm_common::sm_common
    sm_timing::sm_timing
    sm_eigen::sm_eigen
    sm_kinematics::sm_kinematics
    sparse_block_matrix::sparse_block_matrix
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

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)
ament_export_include_directories(include)
ament_export_dependencies(sm_common sm_timing sm_eigen sm_kinematics sparse_block_matrix Eigen3)

ament_package()
