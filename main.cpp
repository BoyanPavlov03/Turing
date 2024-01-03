#include "HPP/TuringMachine.hpp"

int main() {
    Tape* tape = new Tape("../tape1.txt");
    TuringMachine tm(tape, "../addOne.txt");
    tm.run();

    delete tape;
    return 0;
}
