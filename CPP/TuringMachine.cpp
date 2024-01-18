#include "../HPP/TuringMachine.hpp"
#include "../HPP/FileOpener.hpp"
#include <iostream>
#include <queue>

TuringMachine::TuringMachine(std::ifstream file) {
    std::string line;
    std::cout << "Loading turing machine...\n";

    std::getline(file, line);
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        states.emplace_back(token);
    }

    std::getline(file, line);
    iss.str(line);
    iss.clear();
    while (std::getline(iss, token, ' ')) {
        alphabet.emplace_back(token);
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
        transitions[std::make_pair(state, read)].emplace_back(new Transition(nextState, write, direction == 'L' ? LEFT : direction == 'R' ? RIGHT : STAY, helperMachine));
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
    if (stopState == "accept") {
        runRecognizer(currentTape);
        return;
    }
    ComputationHistoryNode* root = new ComputationHistoryNode(new Tape(*currentTape));
    executeTransitionsUntilStopState(root);
    if (currentState == "accept") {
        std::cout << "The language representing the turing machine accepts the word from the tape!\n";
    } else if (currentState == "halt") {
        root->writeToFileAllLeafs("../Resources/outputTape.txt");
        root->graphVizPrint();
        std::cout << "Turing machine finished successfully!\n";
    } else {
        std::cout << "The language representing the turing machine rejects the word from the tape!\n";
    }

    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        ComputationHistoryNode* node = nodes.front();
        nodes.pop();
        for (auto& child : node->children) {
            nodes.push(child);
        }
        delete node;
    }
}

void TuringMachine::executeTransition(ComputationHistoryNode* root, Transition* transition) {
    std::cout << root->tape->toString() << "\n";
    if (!transition->helperMachine.empty()) {
        TuringMachine* helperMachine = new TuringMachine(FileOpener::openFile(transition->helperMachine));
        std::string preservedState = root->currentState;
        helperMachine->setTape(root->tape);
        helperMachine->executeTransitionsUntilStopState(root);
        delete helperMachine;
        std::queue<ComputationHistoryNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            ComputationHistoryNode* node = nodes.front();
            nodes.pop();
            if (node->children.empty()) {
                std::vector<Transition*> currentStateTransitions = transitions.at(std::make_pair(preservedState,
                                                                                node->tape->tapeContent.at(node->tape->index)));
                for (auto& t : currentStateTransitions) {
                    executeTransition(node, t);
                }
            } else {
                for (auto& child : node->children) {
                    nodes.push(child);
                }
            }
        }
        return;
    }
    Tape* tape = new Tape(*root->tape);
    tape->tapeContent.at(tape->index) = transition->write;
    switch (transition->command) {
        case LEFT:
            if (tape->index == 0)
                return;
            tape->index--;
            break;
        case RIGHT:
            if (tape->tapeContent.size() == tape->index + 1) {
                tape->tapeContent.emplace_back("_");
            }
            tape->index++;
        case STAY:
            break;
    }
    ComputationHistoryNode* newNode = new ComputationHistoryNode(tape);
    root->children.emplace_back(newNode);
    newNode->currentState = transition->newState;
    newNode->command = transition->command;
    if (transition->newState == stopState) {
        currentState = stopState;
        return;
    }
    std::vector<Transition*> currentStateTransitions = transitions.at(std::make_pair(transition->newState,
                                                                                     tape->tapeContent.at(tape->index)));
    for (auto& t : currentStateTransitions) {
        executeTransition(newNode, t);
    }
}

void TuringMachine::executeTransitionsUntilStopState(ComputationHistoryNode* root) {
    currentState = startState;
    root->tape->index = 1;
    root->currentState = currentState;
    try {
        std::vector<Transition*> currentStateTransitions = transitions.at(std::make_pair(root->currentState,
                                                                                         root->tape->tapeContent.at(root->tape->index)));
        for (auto& t : currentStateTransitions) {
            executeTransition(root, t);
        }
    } catch (std::out_of_range& e) {
        if (currentState != stopState) {
            currentState = "reject";
        }
    }
}

void TuringMachine::composition(TuringMachine* other) {
    ComputationHistoryNode* root = new ComputationHistoryNode(new Tape(*currentTape));
    other->setTape(root->tape);
    other->executeTransitionsUntilStopState(root);
    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        ComputationHistoryNode* node = nodes.front();
        nodes.pop();
        if (node->children.empty()) {
            executeTransitionsUntilStopState(node);
        } else {
            for (auto& child : node->children) {
                nodes.push(child);
            }
        }
    }
    root->writeToFileAllLeafs("../Resources/outputTape.txt");
    root->graphVizPrint();
}

void TuringMachine::runAnotherMachineBasedOnCurrentState(TuringMachine* acceptor, TuringMachine* rejector) {
    if (runRecognizer(currentTape)) {
        acceptor->setTape(currentTape);
        acceptor->run();
    } else {
        std::cout << currentTape->toString() << "\n";
        rejector->setTape(currentTape);
        rejector->run();
    }
}

bool TuringMachine::runRecognizer(Tape* tape) {
    ComputationHistoryNode* root = new ComputationHistoryNode(new Tape(*tape));
    setTape(root->tape);
    executeTransitionsUntilStopState(root);
    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        ComputationHistoryNode* node = nodes.front();
        nodes.pop();
        if (node->children.empty()) {
            if (node->currentState == "accept") {
                currentState = "accept";
                return true;
            }
        } else {
            for (auto& child : node->children) {
                nodes.push(child);
            }
        }
        delete node;
    }
    return false;
}

void TuringMachine::runWhile(TuringMachine* predicate) {
    if (predicate->stopState != "accept") {
        std::cout << "Predicate must be acceptor!\n";
        return;
    }
    ComputationHistoryNode* root = new ComputationHistoryNode(new Tape(*currentTape));
    runWhileHelper(predicate, root);
    std::cout << "Turing machine finished successfully!\n";
    root->writeToFileAllLeafs("../Resources/outputTape.txt");
    root->graphVizPrint();
}

void TuringMachine::runWhileHelper(TuringMachine* predicate, ComputationHistoryNode* root) {
    if (!predicate->runRecognizer(root->tape)) {
        return;
    }
    executeTransitionsUntilStopState(root);
    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        ComputationHistoryNode* node = nodes.front();
        nodes.pop();
        if (node->children.empty()) {
            runWhileHelper(predicate, node);
        } else {
            for (auto& child : node->children) {
                nodes.push(child);
            }
        }
    }
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