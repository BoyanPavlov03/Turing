#include "../HPP/TuringMachine.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

TuringMachine::TuringMachine(Tape* tape, const std::string& fileName) : tape(tape) {
    std::ifstream file(fileName);
    std::string line;

    std::getline(file, line);
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        states.push_back(token);
    }

    std::getline(file, line);
    iss.str(line);
    iss.clear();
    while (std::getline(iss, token, ' ')) {
        alphabet.push_back(token);
    }

    std::getline(file, currentState);

    std::getline(file, line);
    iss.str(line);
    iss.clear();
    while (std::getline(iss, token, ' ')) {
        finalStates.push_back(token);
    }

    while (std::getline(file, line)) {
        std::string state, read, write, nextState;
        char direction;
        std::stringstream ss(line);
        ss >> state >> read >> nextState >> write >> direction;
        transitions[std::make_pair(state, read)] = new Transition(nextState, write, direction == 'L' ? LEFT : direction == 'R' ? RIGHT : STAY);
    }
    file.close();
    std::cout << "Turing machine loaded successfully!\n";
}

void TuringMachine::run() {
    executeUntilStopState();
    clearEmptyTapeNodesAtTheEnd();
    tape->writeToFile("../output1.txt");
    std::cout << "Turing machine finished successfully!\n";
}

void TuringMachine::runTransition(Transition* transition) {
    tape->current->data = transition->write;
    currentState = transition->newState;
    switch (transition->command) {
        case LEFT:
            if (tape->current->prev == nullptr)
                return;
            tape->current = tape->current->prev;
            break;
        case RIGHT:
            if (tape->current->next == nullptr) {
                TapeNode* newNode = new TapeNode("_", nullptr, tape->current);
                tape->current->next = newNode;
                tape->tail = newNode;
            }
            tape->current = tape->current->next;
        case STAY:
            break;
    }
}

void TuringMachine::executeUntilStopState() {
    while(std::find(finalStates.begin(), finalStates.end(), currentState) == finalStates.end()) {
        Transition* transition = transitions.at(std::make_pair(currentState, tape->current->data));
        runTransition(transition);
    }
}

void TuringMachine::clearEmptyTapeNodesAtTheEnd() {
    while (tape->tail->data == "_") {
        TapeNode* temp = tape->tail;
        tape->tail = tape->tail->prev;
        tape->tail->next = nullptr;
        delete temp;
    }
}