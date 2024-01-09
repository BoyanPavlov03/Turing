#include "../HPP/Tape.hpp"
#include <fstream>
#include <sstream>
#include <iostream>


Tape::Tape(std::ifstream file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string letter;
    while (std::getline(iss, letter, ' ')) {
        tapeContent.emplace_back(letter);
    }
    file.close();
}

void Tape::writeToFile(const std::string& fileName) {
    std::ofstream file(fileName);
    for (auto& letter : tapeContent) {
        file << letter << " ";
    }
    file.close();
}

void Tape::print() {
    for (auto& letter : tapeContent) {
        std::cout << letter << " ";
    }
    std::cout << "\n";
}

std::string Tape::toString() {
    std::string result;
    for (auto& letter : tapeContent) {
        result += letter + " ";
    }
    result.pop_back();
    return result;
}

void Tape::removeAllLastEmptySymbol() {
    while (tapeContent.back() == "_") {
        tapeContent.pop_back();
    }
}