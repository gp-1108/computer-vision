# HOW TO BUILD:
# 1. mkdir build && cd build
# 2. cmake ../
# 3. cmake --build .
# The different executables will be available in the build folder as "exec_task1", "exec_task2", etc.
cmake_minimum_required(VERSION 3.5)

project(lab01
  VERSION 1.0
  DESCRIPTION "Lab 01 for computer vision course"
  LANGUAGES CXX)

find_package(OpenCV REQUIRED)

add_executable(exec_task1 task1.cpp)
target_link_libraries(exec_task1 ${OpenCV_LIBS})

add_executable(exec_task2 task2.cpp)
target_link_libraries(exec_task2 ${OpenCV_LIBS})

add_executable(exec_task3 task3.cpp)
target_link_libraries(exec_task3 ${OpenCV_LIBS})

add_executable(exec_task4 task4.cpp)
target_link_libraries(exec_task4 ${OpenCV_LIBS})

add_executable(exec_task5 task5.cpp)
target_link_libraries(exec_task5 ${OpenCV_LIBS})