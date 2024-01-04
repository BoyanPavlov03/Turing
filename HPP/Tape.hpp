#pragma once
#include <string>

struct TapeNode {
    std::string dataForWrite;
    std::string tempData;
    TapeNode* next;
    TapeNode* prev;

    TapeNode(std::string dataForWrite, std::string tempData, TapeNode* next, TapeNode* prev);
};

struct Tape {
    TapeNode *head;
    TapeNode *tail;
    TapeNode *current;

    Tape(const std::string& fileName);
    Tape(const Tape& other);
    ~Tape();
    void writeToFile(const std::string& fileName);
    void print();
};