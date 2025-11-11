cmake_minimum_required(VERSION 3.16)
project(sm_common)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ROS 2
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -D__STRICT_ANSI__")

# Create library
add_library(${PROJECT_NAME}
  src/progress_info.cpp
)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} 
  PUBLIC
    Boost::system
)

target_compile_options(${PROJECT_NAME} PUBLIC "-Wno-deprecated-copy") # TODO: Fix...

##################
## Installation ##
##################

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

## Mark cpp header files for installation
install(DIRECTORY include/
  DESTINATION include
)

# Export targets
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
)

#############
## Testing ##
#############
if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  
  # Avoid clash with tr1::tuple: https://code.google.com/p/googletest/source/browse/trunk/README?r=589#257
  add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=0)

  ament_add_gtest(${PROJECT_NAME}-test
    test/test_main.cpp
    test/maths.cpp
    test/serialization_macros.cpp
    test/numerical_comparisons.cpp
    test/hash_id.cpp
  )
  target_link_libraries(${PROJECT_NAME}-test pthread ${PROJECT_NAME})
endif()

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)

ament_package(CONFIG_EXTRAS cmake/export_flags.cmake)
