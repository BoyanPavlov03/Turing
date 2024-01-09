#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Tape.hpp"

struct ComputationHistoryNode {
    Tape* tape;
    std::string currentState;
    std::vector<ComputationHistoryNode*> children;

    ComputationHistoryNode(Tape* tape) {
        this->tape = tape;
    }

    void writeToFileAllLeafs(const std::string& fileName) {
        std::ofstream file(fileName);
        std::queue<ComputationHistoryNode*> nodes;
        nodes.push(this);
        while (!nodes.empty()) {
            ComputationHistoryNode* node = nodes.front();
            nodes.pop();
            if (node->children.empty()) {
                node->tape->removeAllLastEmptySymbol();
                std::cout << node->tape->toString() << "\n";
                file << node->tape->toString() << " ";
            } else {
                for (auto& child : node->children) {
                    nodes.push(child);
                }
            }
        }
        file.close();
    }
};