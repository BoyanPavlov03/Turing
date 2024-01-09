#pragma once
#include <string>

struct Tape {
    std::vector<std::string> tapeContent;
    unsigned index;

    Tape(std::ifstream file);
    Tape(const Tape& other) {
        tapeContent = other.tapeContent;
        index = other.index;
    }
    void writeToFile(const std::string& fileName);
    void print();
    std::string toString();
    void removeAllLastEmptySymbol();
};