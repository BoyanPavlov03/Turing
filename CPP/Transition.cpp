#include "../HPP/Transition.hpp"
#include <string>

Transition::Transition(std::string newState, std::string write, Command command, std::string helperMachine) {
    this->newState = newState;
    this->write = write;
    this->command = command;
    this->helperMachine = helperMachine;
}