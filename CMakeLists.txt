cmake_minimum_required(VERSION 3.20)
Project(NoiseMachine-PanBot VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(extern)
add_subdirectory(src bin)
add_subdirectory(test)