cmake_minimum_required(VERSION 3.16)
project(numpy_eigen)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(python_module REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen3 REQUIRED)

add_definitions(${EIGEN_DEFINITIONS})
add_definitions(-D__STRICT_ANSI__)

# ignore "error: return-statement with a value, in function returning 'void'" in "__multiarray_api.h"
add_compile_options(-fpermissive)

IF(APPLE)
  link_directories( /usr/local/lib )
ENDIF(APPLE)

##############
## Building ##
##############

INCLUDE(src/autogen_files.cmake)
add_python_export_library(${PROJECT_NAME} 
  ${PROJECT_SOURCE_DIR}/python/${PROJECT_NAME} ${AUTOGEN_FILES}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${EIGEN3_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Boost::system
    ${Boost_LIBRARIES}
    Eigen3::Eigen
)

INCLUDE(src/autogen_test_files.cmake)
add_python_export_library(${PROJECT_NAME}_test 
  ${PROJECT_SOURCE_DIR}/python/${PROJECT_NAME} ${AUTOGEN_TEST_FILES}
)

#############
## Testing ##
#############
if(BUILD_TESTING)
  # Python testing with pytest
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(numpy_eigen_test test/numpy_eigen_tests.py)
endif()

##################
## Installation ##
##################

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_test
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(Boost Eigen3)

ament_package(CONFIG_EXTRAS cmake/numpy_eigen-extras.cmake)


IF(APPLE)
  link_directories( /usr/local/lib )
ENDIF(APPLE)
