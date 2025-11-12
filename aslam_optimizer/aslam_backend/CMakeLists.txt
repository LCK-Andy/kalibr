cmake_minimum_required(VERSION 3.16)
project(aslam_backend)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake policy for Boost
cmake_policy(SET CMP0167 OLD)

find_package(ament_cmake REQUIRED)
# Find external dependencies FIRST before importing targets that depend on them
find_package(Boost REQUIRED COMPONENTS system thread serialization)
find_package(Eigen3 REQUIRED)
find_package(TBB REQUIRED)

find_package(sparse_block_matrix REQUIRED)
find_package(sm_boost REQUIRED)
find_package(sm_random REQUIRED)
find_package(sm_timing REQUIRED)
find_package(sm_logging REQUIRED)
find_package(sm_property_tree REQUIRED)

add_library(${PROJECT_NAME}
  src/MEstimatorPolicies.cpp
  src/JacobianContainer.cpp
  src/DesignVariable.cpp
  src/ErrorTerm.cpp
  src/OptimizationProblemBase.cpp
  src/Optimizer.cpp
  src/sparse_matrix_functions.cpp
  src/OptimizationProblem.cpp
  src/SimpleOptimizationProblem.cpp
  src/JacobianBuilder.cpp
  src/LinearSystemSolver.cpp
  src/BlockCholeskyLinearSystemSolver.cpp
  src/SparseCholeskyLinearSystemSolver.cpp
  src/SparseQrLinearSystemSolver.cpp
  src/Matrix.cpp
  src/DenseMatrix.cpp
  src/SparseBlockMatrixWrapper.cpp
  src/DenseQrLinearSystemSolver.cpp
  src/BlockCholeskyLinearSolverOptions.cpp
  src/SparseCholeskyLinearSolverOptions.cpp
  src/SparseQRLinearSolverOptions.cpp
  src/DenseQRLinearSolverOptions.cpp
  src/TrustRegionPolicy.cpp
  src/ErrorTermDs.cpp
  src/GaussNewtonTrustRegionPolicy.cpp
  src/LevenbergMarquardtTrustRegionPolicy.cpp
  src/Marginalizer.cpp
  src/MarginalizationPriorErrorTerm.cpp
  src/DogLegTrustRegionPolicy.cpp
  src/Optimizer2.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    sparse_block_matrix::sparse_block_matrix
    sm_boost::sm_boost
    sm_random::sm_random
    sm_timing::sm_timing
    sm_logging::sm_logging
    sm_property_tree::sm_property_tree
    Boost::system
    Boost::thread
    Boost::serialization
    Eigen3::Eigen
)

##############
## Testing ##
##############

if(BUILD_TESTING)
  enable_testing()
  find_package(ament_cmake_gtest REQUIRED)
  
  # Avoid clash with tr1::tuple: https://code.google.com/p/googletest/source/browse/trunk/README?r=589#257
  add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=0)
  
  ament_add_gtest(${PROJECT_NAME}_test
    test/test_main.cpp
    test/JacobianContainer.cpp
    test/test_sparse_matrix_functions.cpp
    test/TestOptimizer.cpp
    test/TestOptimizationProblem.cpp
    test/CompressedColumnMatrixTest.cpp
    test/MatrixTestHarness.cpp
    test/DenseMatrixTest.cpp
    test/SparseMatrixTest.cpp
    test/LinearSolverTests.cpp
    test/ErrorTermTests.cpp
  )
  target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
endif()

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
ament_export_dependencies(sparse_block_matrix sm_boost sm_random sm_timing sm_logging sm_property_tree Boost Eigen3)

ament_package()
