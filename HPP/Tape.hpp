#pragma once
#include <string>

struct TapeNode {
    std::string data;
    TapeNode* next;
    TapeNode* prev;

    TapeNode(std::string data, TapeNode* next, TapeNode* prev);
};

struct Tape {
    TapeNode *head;
    TapeNode *tail;
    TapeNode *current;

    Tape(const std::string& fileName);
    void writeToFile(const std::string& fileName);
};