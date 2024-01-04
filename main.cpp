#include "HPP/TuringMachine.hpp"

int main() {
    Tape* tape = new Tape("/Users/boyan/Desktop/Turing/tape.txt");
//    TuringMachine* recognizer = new TuringMachine("/Users/boyan/Desktop/Turing/zero^n_one^n.txt");
//    TuringMachine* addOne = new TuringMachine("/Users/boyan/Desktop/Turing/addOne.txt");
//    TuringMachine* swapDigits = new TuringMachine("/Users/boyan/Desktop/Turing/swapDigits.txt");
    TuringMachine* equalOnesAndZeroes = new TuringMachine("/Users/boyan/Desktop/Turing/equalOnesAndZeroes.txt");
    TuringMachine* shiftRightBinary = new TuringMachine("/Users/boyan/Desktop/Turing/shiftRightBinary.txt");

//    addOne->setTape(tape);
//    addOne->run();
//    recognizer->setTape(tape);
    shiftRightBinary->setTape(tape);
    shiftRightBinary->runWhile(equalOnesAndZeroes);
//    swapDigits->setTape(tape);
//    recognizer->runAnotherMachineBasedOnCurrentState(addOne, swapDigits);
//    shiftRightBinary->setTape(tape);
//    shiftRightBinary->run();

    delete tape;
    return 0;
}
