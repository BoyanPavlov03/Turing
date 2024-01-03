#pragma once
#include <string>
#include "Command.hpp"

struct Transition {
    std::string newState;
    std::string write;
    Command command;

    Transition(std::string newState, std::string write, Command command);
};