#pragma once
#include <string>
#include "Command.hpp"

struct Transition {
    std::string newState;
    std::string write;
    Command command;
    std::string helperMachine;

    Transition(std::string newState, std::string write, Command command, std::string helperMachine);
};