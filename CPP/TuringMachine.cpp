#include "../HPP/TuringMachine.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

TuringMachine::TuringMachine(const std::string& fileName) {
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

    std::getline(file, startState);
    currentState = startState;

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

void TuringMachine::run(Tape* tape) {
    if (!checkIfTapeIsInAlphabet(tape)) {
        std::cout << "Tape is not in alphabet!\n";
        return;
    }

    executeUntilStopState(tape);
    clearEmptyTapeNodesAtTheEnd(tape);
    tape->writeToFile("../../output1.txt");
    if (currentState == "accept")
        std::cout << "The language representing the turing machine accepts the word from the tape!\n";
    else if (currentState == "halt")
        std::cout << "Turing machine finished successfully!\n";
    else
        std::cout << "The language representing the turing machine rejects the word from the tape!\n";

    currentState = startState;
}

void TuringMachine::runTransition(Transition* transition, Tape* tape) {
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

void TuringMachine::executeUntilStopState(Tape* tape) {
    Tape* workingTape = new Tape(*tape);

    while(currentState != "halt" && currentState != "reject" && currentState != "accept") {
        try {
            Transition* transition = transitions.at(std::make_pair(currentState, workingTape->current->data));
            runTransition(transition, workingTape);
        } catch (std::out_of_range& e) {
            currentState = "reject";
        }
    }

    if (currentState == "halt") {
        *tape = *workingTape;
    }
}

void TuringMachine::clearEmptyTapeNodesAtTheEnd(Tape* tape) {
    while (tape->tail->data == "_") {
        TapeNode* temp = tape->tail;
        tape->tail = tape->tail->prev;
        tape->tail->next = nullptr;
        delete temp;
    }
}

bool TuringMachine::checkIfTapeIsInAlphabet(Tape* tape) {
    for (TapeNode* node = tape->head; node != nullptr; node = node->next) {
        if (std::find(alphabet.begin(), alphabet.end(), node->data) == alphabet.end()) {
            std::cout << node->data << "\n";
            return false;
        }
    }
    return true;
}

void TuringMachine::composition(Tape* tape, TuringMachine* other) {
    if (!checkIfTapeIsInAlphabet(tape) || !other->checkIfTapeIsInAlphabet(tape)) {
        std::cout << "Tape is not in alphabet!\n";
        return;
    }
    other->executeUntilStopState(tape);
    run(tape);
}

void TuringMachine::runAnotherMachineBasedOnCurrentState(Tape* tape, TuringMachine* acceptor, TuringMachine* rejector) {
    executeUntilStopState(tape);
    if (currentState == "accept") {
        acceptor->run(tape);
    } else if (currentState == "reject") {
        rejector->run(tape);
    } else {
        std::cout << "Turing machine is not in accept or reject state!\n";
    }
    currentState = startState;
}