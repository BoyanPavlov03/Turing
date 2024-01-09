#include "HPP/TuringMachine.hpp"
#include "HPP/FileOpener.hpp"
#include "doctest.h"
#include <iostream>

int main() {
//    Tape* tape = new Tape(FileOpener::openFile("/Users/boyan/Desktop/Turing/tape.txt"));
//    TuringMachine* recognizer = new TuringMachine("/Users/boyan/Desktop/Turing/zero^n_one^n.txt");
//    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
//    TuringMachine* swapDigits = new TuringMachine("/Users/boyan/Desktop/Turing/swapDigits.txt");
//    TuringMachine* equalOnesAndZeroes = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/notEqualOnesAndZeroes.txt"));
//    TuringMachine* shiftRightBinary = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/shiftRightBinary.txt"));

//    addOne->setTape(tape);
//    addOne->run();
//    recognizer->setTape(tape);
//    shiftRightBinary->setTape(tape);
//    shiftRightBinary->runWhile(equalOnesAndZeroes);
//    swapDigits->setTape(tape);
//    recognizer->runAnotherMachineBasedOnCurrentState(addOne, swapDigits);
//    shiftRightBinary->setTape(tape);
//    shiftRightBinary->run();

//    delete tape;
//    delete equalOnesAndZeroes;
//    delete shiftRightBinary;

    doctest::Context().run();
//    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 1 1 1"));
//    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
//    addOne->setTape(tape);
//    addOne->run();
//    CHECK(addOne->getCurrentState() == "halt");
//    CHECK(tape->toString() == "$ 1 0 0 0");
//    delete tape;
//    delete addOne;
    return 0;
}
