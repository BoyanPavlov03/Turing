#include "HPP/TuringMachine.hpp"
#include "HPP/FileOpener.hpp"
#include "doctest.h"

int main() {
    Tape* tape = new Tape(FileOpener::openFile("/Users/boyan/Desktop/Turing/tape.txt"));
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
    return 0;
}
