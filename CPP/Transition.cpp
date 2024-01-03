#include "../HPP/Transition.hpp"
#include <string>

Transition::Transition(std::string newState, std::string write, Command command) : newState(newState), write(write), command(command) {}