#include "HPP/TuringMachine.hpp"

int main() {
    Tape* tape = new Tape("../tape1.txt");
    TuringMachine* recognizer = new TuringMachine("../zero^n_one^n.txt");
    TuringMachine* addOne = new TuringMachine("../addOne.txt");
    TuringMachine* swapDigits = new TuringMachine("../swapDigits.txt");

    recognizer->runAnotherMachineBasedOnCurrentState(tape, addOne, swapDigits);

    delete tape;
    return 0;
}
