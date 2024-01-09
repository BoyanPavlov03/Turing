#pragma once
#include <string>
#include <iostream>

struct Tape {
    std::vector<std::string> tapeContent;
    unsigned index = 0;

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