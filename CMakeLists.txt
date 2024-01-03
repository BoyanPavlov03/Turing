cmake_minimum_required(VERSION 3.24)
project(Turing)

set(CMAKE_CXX_STANDARD 17)

add_executable(Turing main.cpp CPP/Transition.cpp CPP/Tape.cpp CPP/TuringMachine.cpp)
