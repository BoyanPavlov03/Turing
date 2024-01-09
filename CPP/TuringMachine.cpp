#include "../HPP/TuringMachine.hpp"
#include "../HPP/FileOpener.hpp"
#include <sstream>
#include <iostream>
#include <queue>

TuringMachine::TuringMachine(std::ifstream file) {
    std::string line;
    std::cout << "Loading turing machine...\n";

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
        transitions[std::make_pair(state, read)].push_back(new Transition(nextState, write, direction == 'L' ? LEFT : direction == 'R' ? RIGHT : STAY, helperMachine));
    }
    file.close();
    std::cout << "Turing machine loaded successfully!\n";
}

TuringMachine::~TuringMachine() {
    for (auto transition : transitions) {
        for (auto t : transition.second) {
            delete t;
        }
    }
}

void TuringMachine::run() {
    if (currentTape == nullptr) {
        std::cout << "Turing machine does not have a tape to operate on!\n";
        return;
    }
    executeTransitionsUntilStopState();
    removeEmptySymbolsAtTheBack();
    currentTape->index = 0;
    if (currentState == "accept")
        std::cout << "The language representing the turing machine accepts the word from the tape!\n";
    else if (currentState == "halt") {
        currentTape->writeToFile("/Users/boyan/Desktop/Turing/tape.txt");
        std::cout << "Turing machine finished successfully!\n";
    } else
        std::cout << "The language representing the turing machine rejects the word from the tape!\n";
}

void TuringMachine::executeTransition(Transition* transition) {
    currentTape->tapeContent.at(currentTape->index) = transition->write;
    if (stopState == "halt") {
        currentTape->tapeContent.at(currentTape->index) = transition->write;
    }
    currentState = transition->newState;
    switch (transition->command) {
        case LEFT:
            if (currentTape->index == 0)
                return;
            currentTape->index--;
            break;
        case RIGHT:
            if (currentTape->tapeContent.size() == currentTape->index + 1) {
                currentTape->tapeContent.emplace_back("_");
            }
            currentTape->index++;
        case STAY:
            break;
    }
}

void TuringMachine::addToQueue(std::queue<Transition*>& transitionsToExecute) {
    std::vector<Transition*> currentStateTransitions = transitions.at(std::make_pair(currentState,
                                                                                     currentTape->tapeContent.at(currentTape->index)));
    for (auto& t : currentStateTransitions) {
        transitionsToExecute.push(t);
    }
}

void TuringMachine::executeTransitionsUntilStopState() {
    currentState = startState;
    std::vector<std::string> tapeBackup = currentTape->tapeContent;
    std::queue<Transition*> transitionsToExecute;
    addToQueue(transitionsToExecute);
    while(!transitionsToExecute.empty()) {
        try {
            Transition* transition = transitionsToExecute.front();
            transitionsToExecute.pop();

            if (!transition->helperMachine.empty()) {
                TuringMachine* helperMachine = new TuringMachine(FileOpener::openFile(transition->helperMachine));
                if (helperMachine->stopState == "accept") {
                    delete helperMachine;
                    transition->helperMachine = "";
                    continue;
                }
                helperMachine->setTape(currentTape);
                helperMachine->executeTransitionsUntilStopState();
                delete helperMachine;
            } else {
                executeTransition(transition);
            }

            if (currentState == "halt" || currentState == "accept") {
                break;
            }

            addToQueue(transitionsToExecute);
        } catch (std::out_of_range& e) {
            currentState = "reject";
        }
    }
    if (stopState == "accept") {
        currentTape->tapeContent = tapeBackup;
    }
}

void TuringMachine::removeEmptySymbolsAtTheBack() {
    while (currentTape->tapeContent.back() == "_") {
        currentTape->tapeContent.pop_back();
    }
}

void TuringMachine::composition(TuringMachine* other) {
    other->setTape(currentTape);
    other->executeTransitionsUntilStopState();
    currentTape->index = 0;
    run();
}

void TuringMachine::runAnotherMachineBasedOnCurrentState(TuringMachine* acceptor, TuringMachine* rejector) {
    executeTransitionsUntilStopState();
    currentTape->index = 0;
    if (currentState == "accept") {
        acceptor->setTape(currentTape);
        acceptor->run();
    } else if (currentState == "reject") {
        rejector->setTape(currentTape);
        rejector->run();
    } else {
        std::cout << "Turing machine is not in accept or reject state!\n";
    }
}

void TuringMachine::runWhile(TuringMachine* predicate) {
    if (predicate->stopState != "accept") {
        std::cout << "Predicate must be acceptor!\n";
        return;
    }
    predicate->setTape(currentTape);
    while(true) {
        predicate->executeTransitionsUntilStopState();
        currentTape->index = 0;
        if (predicate->currentState != "accept") {
            break;
        }
        run();
    }
    removeEmptySymbolsAtTheBack();
}

void TuringMachine::setTape(Tape* tape) {
    for (int i = 0; i < tape->tapeContent.size(); i++) {
        if (tape->tapeContent.at(i) == "$" && i == 0) continue;
        if (std::find(alphabet.begin(), alphabet.end(), tape->tapeContent.at(i)) == alphabet.end()) {
            std::cout << "The tape content is not in the alphabet of the turing machine!\n";
            return;
        }
    }
    currentTape = tape;
}

std::string TuringMachine::getCurrentState() {
    return currentState;
}