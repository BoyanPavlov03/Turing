#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Tape.hpp"
#include "Command.hpp"

struct ComputationHistoryNode {
    Tape* tape;
    std::string currentState;
    Command command;
    std::vector<ComputationHistoryNode*> children;

    ComputationHistoryNode(Tape* tape);
    void writeToFileAllLeafs(const std::string& fileName);
    void graphVizPrint();
};