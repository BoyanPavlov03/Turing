#include "../HPP/Tape.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

TapeNode::TapeNode(std::string dataForWrite, std::string tempData, TapeNode* next, TapeNode* prev)
: dataForWrite(dataForWrite), tempData(tempData), next(next), prev(prev) {}

Tape::Tape(const std::string& fileName) : head(nullptr), current(nullptr), tail(nullptr) {
    std::ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string letter;
    while (std::getline(iss, letter, ' ')) {
        TapeNode* newNode = new TapeNode(letter, letter, nullptr, nullptr);
        if (head == nullptr) {
            head = newNode;
        } else {
            TapeNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    current = head;
    tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    file.close();
}

Tape::Tape(const Tape& other) : head(nullptr), current(nullptr), tail(nullptr) {
    TapeNode* temp = other.head;
    while (temp != nullptr) {
        TapeNode* newNode = new TapeNode(temp->dataForWrite, temp->tempData, nullptr, nullptr);
        if (head == nullptr) {
            head = newNode;
        } else {
            TapeNode* temp2 = head;
            while (temp2->next != nullptr) {
                temp2 = temp2->next;
            }
            temp2->next = newNode;
            newNode->prev = temp2;
        }
        if (temp->next == nullptr) tail = temp;
        temp = temp->next;
    }
    current = head;
}

Tape::~Tape() {
    TapeNode* temp = head;
    while (temp != nullptr) {
        TapeNode* temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
}

void Tape::writeToFile(const std::string& fileName) {
    std::ofstream file(fileName);
    TapeNode* temp = head;
    while (temp != nullptr) {
        file << temp->dataForWrite << " ";
        temp = temp->next;
    }
    file.close();
}

void Tape::print() {
    TapeNode* temp = head;
    while (temp != nullptr) {
        std::cout << "Data for write: " << temp->dataForWrite << ", temp data: " << temp->tempData << "\n";
        temp = temp->next;
    }
    std::cout << "\n";
}