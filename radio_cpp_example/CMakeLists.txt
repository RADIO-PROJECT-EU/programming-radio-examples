cmake_minimum_required(VERSION 2.8.3)
project(radio_cpp_example)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    radio_services)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS} src)


add_executable(${PROJECT_NAME} src/cpp_example.cpp)
target_link_libraries( ${PROJECT_NAME} ${catkin_LIBRARIES})