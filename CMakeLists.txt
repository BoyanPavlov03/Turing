cmake_minimum_required(VERSION 3.24)
project(Turing)

set(CMAKE_CXX_STANDARD 17)

add_executable(Turing main.cpp CPP/Transition.cpp CPP/Tape.cpp CPP/TuringMachine.cpp doctest.h Tests/TapeTest.cpp Tests/TuringMachineTest.cpp HPP/FileOpener.hpp HPP/ComputationHistoryNode.hpp CPP/ComputationHistoryNode.cpp CPP/FileOpener.cpp HPP/HashPair.hpp)
