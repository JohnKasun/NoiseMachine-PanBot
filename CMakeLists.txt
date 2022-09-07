cmake_minimum_required(VERSION 3.20)
Project(NoiseMachine-Panner VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern)
add_subdirectory(src bin)
add_subdirectory(test)

include_directories(include)