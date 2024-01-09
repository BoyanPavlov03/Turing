#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Tape.hpp"

struct ComputationHistoryNode {
    Tape* tape;
    std::string currentState;
    std::vector<ComputationHistoryNode*> children;

    ComputationHistoryNode(Tape* tape);
    void writeToFileAllLeafs(const std::string& fileName);
};