project(NeuralNet)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

aux_source_directory(. SRC_LIST)
add_subdirectory(Network)
add_subdirectory(Solver)

find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} Network Solver)
