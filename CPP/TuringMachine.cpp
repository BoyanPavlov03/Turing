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

    std::getline(file, stopState);

    while (std::getline(file, line)) {
        std::string state, read, write, nextState;
        char direction;
        std::stringstream ss(line);
        std::string helperMachine;
        ss >> state >> read >> nextState >> write >> direction >> helperMachine;
        transitions[std::make_pair(state, read)] = new Transition(nextState, write, direction == 'L' ? LEFT : direction == 'R' ? RIGHT : STAY, helperMachine);
    }
    file.close();
    std::cout << "Turing machine loaded successfully!\n";
}

void TuringMachine::run() {
    executeTransitionsUntilStopState();
    clearEmptyTapeNodesAtTheEnd();
    if (currentState == "accept")
        std::cout << "The language representing the turing machine accepts the word from the tape!\n";
    else if (currentState == "halt") {
        currentTape->writeToFile("/Users/boyan/Desktop/Turing/tape.txt");
        std::cout << "Turing machine finished successfully!\n";
    } else
        std::cout << "The language representing the turing machine rejects the word from the tape!\n";
}

void TuringMachine::executeTransition(Transition* transition) {
    currentTape->current->tempData = transition->write;
    if (stopState == "halt") {
        currentTape->current->dataForWrite = transition->write;
    }
    currentState = transition->newState;
    switch (transition->command) {
        case LEFT:
            if (currentTape->current->prev == nullptr)
                return;
            currentTape->current = currentTape->current->prev;
            break;
        case RIGHT:
            if (currentTape->current->next == nullptr) {
                TapeNode* newNode = new TapeNode("_", "_", nullptr, currentTape->current);
                currentTape->current->next = newNode;
                currentTape->tail = newNode;
            }
            currentTape->current = currentTape->current->next;
        case STAY:
            break;
    }

}

void TuringMachine::executeTransitionsUntilStopState() {
    currentState = startState;
    while(currentState != "reject" && currentState != "accept" && currentState != "halt") {
        try {
            std::string tapeData = stopState == "accept"
                                   ? currentTape->current->tempData
                                   : currentTape->current->dataForWrite;
            Transition* transition = transitions.at(std::make_pair(currentState,tapeData));
//            if (!transition->helperMachine.empty()) {
//                TuringMachine* helperMachine = new TuringMachine(transition->helperMachine);
//                if (helperMachine->stopState == "accept") {
//                    delete helperMachine;
//                    transition->helperMachine = "";
//                    continue;
//                }
//                helperMachine->setTape(currentTape);
//                helperMachine->executeTransitionsUntilStopState();
//                delete helperMachine;
//                continue;
//            }
            executeTransition(transition);
        } catch (std::out_of_range& e) {
            currentState = "reject";
        }
    }
    currentTape->current = currentTape->head;

    for (TapeNode* node = currentTape->head; node != nullptr; node = node->next) {
        node->tempData = node->dataForWrite;
    }
}

void TuringMachine::clearEmptyTapeNodesAtTheEnd() {
    while (currentTape->tail->dataForWrite == "_") {
        TapeNode* temp = currentTape->tail;
        currentTape->tail = currentTape->tail->prev;
        currentTape->tail->next = nullptr;
        delete temp;
    }
}

void TuringMachine::composition(TuringMachine* other) {
    other->setTape(currentTape);
    other->executeTransitionsUntilStopState();
    run();
}

void TuringMachine::runAnotherMachineBasedOnCurrentState(TuringMachine* acceptor, TuringMachine* rejector) {
    executeTransitionsUntilStopState();
    if (currentState == "accept") {
        acceptor->run();
    } else if (currentState == "reject") {
        rejector->run();
    } else {
        std::cout << "Turing machine is not in accept or reject state!\n";
    }
}

void TuringMachine::runWhile(TuringMachine* predicate) {
    predicate->setTape(currentTape);
    do {
        currentTape->print();
        predicate->executeTransitionsUntilStopState();
        if (predicate->currentState == "accept") {
            run();
        }
    } while (predicate->currentState == "accept");

//    currentTape->writeToFile("/Users/boyan/Desktop/Turing/tape.txt");
}

void TuringMachine::setTape(Tape* tape) {
    for (TapeNode* node = tape->head; node != nullptr; node = node->next) {
        if (node->dataForWrite == "$") continue;
        if (std::find(alphabet.begin(), alphabet.end(), node->dataForWrite) == alphabet.end()) {
            std::cout << "Tape is not in alphabet!\n";
            std::cout << "Tape data: " << node->dataForWrite << "\n";
            return;
        }
    }
    currentTape = tape;
}