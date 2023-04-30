# HOW TO BUILD:
# Follow the steps below to build the project: (assuming you are starting from the root folder of the project)
# 1. mkdir build && cd build
# 2. cmake ../
# 3. cmake --build .
# The different executables will be available in the build folder as "exec_task1", "exec_task2", etc.

cmake_minimum_required(VERSION 3.0)

project(Lab04
  VERSION 1.0
  DESCRIPTION "Lab05 for computer vision's tasks"
  LANGUAGES CXX)

find_package(OpenCV 4 REQUIRED)

add_executable(exec_task1 task1.cpp helper_funcs.cpp)
target_link_libraries(exec_task1 PRIVATE ${OpenCV_LIBS})

add_executable(exec_task2 task2.cpp helper_funcs.cpp)
target_link_libraries(exec_task2 PRIVATE ${OpenCV_LIBS})

add_executable(exec_task3 task3.cpp helper_funcs.cpp)
target_link_libraries(exec_task3 PRIVATE ${OpenCV_LIBS})