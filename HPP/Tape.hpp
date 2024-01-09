#pragma once
#include <string>

struct Tape {
    std::vector<std::string> tapeContent;
    unsigned index;

    Tape(std::ifstream file);
    void writeToFile(const std::string& fileName);
    void print();
    std::string toString();
};