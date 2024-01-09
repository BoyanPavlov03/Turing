#include "HPP/TuringMachine.hpp"
#include "HPP/FileOpener.hpp"
#include "doctest.h"
#include <iostream>

int main() {
    doctest::Context().run();
    while (true) {
        std::cout << "Enter command: ";
        std::string command;
        std::getline(std::cin, command);
        std::istringstream iss(command);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ' ')) {
            tokens.emplace_back(token);
        }
        if (tokens[0] == "exit") {
            break;
        } else if (tokens[0] == "run") {
            if (tokens.size() != 3) {
                std::cout << "Invalid number of arguments!\n";
                continue;
            }
            TuringMachine *machine = new TuringMachine(FileOpener::openFile(tokens[1]));
            Tape *tape = new Tape(FileOpener::openFile(tokens[2]));
            machine->setTape(tape);
            machine->run();
            delete machine;
            delete tape;
        } else if (tokens[0] == "runWhile") {
            if (tokens.size() != 4) {
                std::cout << "Invalid number of arguments!\n";
                continue;
            }
            TuringMachine *predicate = new TuringMachine(FileOpener::openFile(tokens[1]));
            TuringMachine *machine = new TuringMachine(FileOpener::openFile(tokens[2]));
            Tape *tape = new Tape(FileOpener::openFile(tokens[3]));
            machine->setTape(tape);
            machine->runWhile(predicate);
            delete predicate;
            delete machine;
            delete tape;
        } else if (tokens[0] == "runMachineDependingOn") {
            if (tokens.size() != 5) {
                std::cout << "Invalid number of arguments!\n";
                continue;
            }
            TuringMachine *recognizer = new TuringMachine(FileOpener::openFile(tokens[1]));
            TuringMachine *acceptor = new TuringMachine(FileOpener::openFile(tokens[2]));
            TuringMachine *rejector = new TuringMachine(FileOpener::openFile(tokens[3]));
            Tape *tape = new Tape(FileOpener::openFile(tokens[4]));
            recognizer->setTape(tape);
            recognizer->runAnotherMachineBasedOnCurrentState(acceptor, rejector);
            delete recognizer;
            delete acceptor;
            delete rejector;
            delete tape;
        } else if (tokens[0] == "composition") {
            if (tokens.size() != 4) {
                std::cout << "Invalid number of arguments!\n";
                continue;
            }
            TuringMachine *first = new TuringMachine(FileOpener::openFile(tokens[1]));
            TuringMachine *second = new TuringMachine(FileOpener::openFile(tokens[2]));
            Tape* tape = new Tape(FileOpener::openFile(tokens[3]));
            first->setTape(tape);
            first->composition(second);
            delete first;
            delete second;
        } else {
            std::cout << "Invalid command!\n";
        }
    }

    return 0;
}
