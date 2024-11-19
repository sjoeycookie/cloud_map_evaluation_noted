cmake_minimum_required(VERSION 3.20.2)

project(cloud_map_evaluation)

set(CMAKE_CXX_STANDARD 17)

find_package(Open3D 0.16.0 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenMP REQUIRED)

find_package(PCL 1.5 REQUIRED)                   #----------------------------------------自己加的

include_directories(
    include
    ${PCL_INCLUDE_DIRS}                                  #----------------------------------------自己加的
    ${Open3D_INCLUDE_DIRS}
)

link_directories(${PCL_LIBRARY_DIRS})         #----------------------------------------自己加的

add_executable(cloud_map_eval src/cloud_map_eval.cpp src/cloud_map_eval_node.cpp)
target_link_libraries(cloud_map_eval ${PCL_LIBRARIES} ${Open3D_LIBRARIES} )                              #----------------------------------------自己加的

# If OpenMP is found, add the flags for OpenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(cloud_map_eval OpenMP::OpenMP_CXX)
endif()