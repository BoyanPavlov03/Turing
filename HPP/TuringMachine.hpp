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
    Tape* tape;
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::unordered_map<std::pair<std::string, std::string>, Transition*, hash_pair> transitions;
    std::vector<std::string> finalStates;
    std::string currentState;

    void runTransition(Transition* transition);
    void executeUntilStopState();
    void clearEmptyTapeNodesAtTheEnd();
public:
    TuringMachine(Tape* tape, const std::string& fileName);
    void run();
//    void composition(TuringMachine* other);
//    void runAnotherMachineBasedOnCurrentState(TuringMachine* acceptor, TuringMachine* rejector);
//    void runWhile(TuringMachine* predicate);
};