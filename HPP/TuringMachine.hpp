#pragma once
#include <string>
#include "Tape.hpp"
#include "Transition.hpp"

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        return hash1;
    }
};

class TuringMachine {
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::unordered_map<std::pair<std::string, std::string>, Transition*, hash_pair> transitions;
    std::string currentState;
    std::string startState;
    std::string stopState;
    Tape* currentTape = nullptr;

    void executeTransition(Transition* transition);
    void executeTransitionsUntilStopState();
    void clearEmptyTapeNodesAtTheEnd();
    bool runRecognizer();
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