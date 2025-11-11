cmake_minimum_required(VERSION 3.16)
project(sm_logging)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ROS 2
find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread regex)

##############
## Building ##
##############

add_library(${PROJECT_NAME} 
  src/Logger.cpp
  src/StdOutLogger.cpp
  src/LoggingEvent.cpp
  src/LoggingGlobals.cpp
  src/Formatter.cpp
  src/Tokens.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Boost::system
    Boost::thread
    Boost::regex
)

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
    test/logTest.cpp
  )
  if(TARGET ${PROJECT_NAME}-test)
    target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
  endif()
endif()

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)

ament_package()
