#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "Tape.hpp"
#include "Transition.hpp"
#include "ComputationHistoryNode.hpp"
#include "HashPair.hpp"

class TuringMachine {
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::unordered_map<std::pair<std::string, std::string>, std::vector<Transition*>, HashPair> transitions;
    std::string currentState;
    std::string startState;
    std::string stopState;
    Tape* currentTape = nullptr;

    void executeTransition(ComputationHistoryNode* root, Transition* transition);
    void executeTransitionsUntilStopState(ComputationHistoryNode* root);
    bool runRecognizer(Tape* tape);
    void runWhileHelper(TuringMachine* predicate, ComputationHistoryNode* root);
public:
    TuringMachine(std::ifstream file);
    ~TuringMachine();
    void setTape(Tape* tape);
    void run();
    void composition(TuringMachine* other);
    void runAnotherMachineBasedOnCurrentState(TuringMachine* acceptor, TuringMachine* rejector);
    void runWhile(TuringMachine* predicate);
    std::string getCurrentState();
};