cmake_minimum_required(VERSION 2.8.3)
project(radio_py_example)

find_package(catkin REQUIRED COMPONENTS
    rospy
    std_msgs
    radio_services)

catkin_package()
