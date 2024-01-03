#include "../HPP/Tape.hpp"
#include <fstream>
#include <sstream>

TapeNode::TapeNode(std::string data, TapeNode* next, TapeNode* prev) : data(data), next(next), prev(prev) {}

Tape::Tape(const std::string& fileName) : head(nullptr), current(nullptr), tail(nullptr) {
    std::ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string letter;
    while (std::getline(iss, letter, ' ')) {
        TapeNode* newNode = new TapeNode(letter, nullptr, nullptr);
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

void Tape::writeToFile(const std::string& fileName) {
    std::ofstream file(fileName);
    TapeNode* temp = head;
    while (temp != nullptr) {
        file << temp->data << " ";
        temp = temp->next;
    }
    file.close();
}