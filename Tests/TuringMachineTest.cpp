#include "../doctest.h"
#include "../HPP/Tape.hpp"
#include "../HPP/TuringMachine.hpp"
#include "../HPP/FileOpener.hpp"

TEST_CASE("TuringMachine::runRecognizer") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/zero^n_one^n.txt"));
    recognizer->setTape(tape);
    recognizer->run();
    CHECK(recognizer->getCurrentState() == "accept");
    delete tape;
    delete recognizer;
}

TEST_CASE("TuringMachine::runRecognizerAndReject") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/zero^n_one^n.txt"));
    recognizer->setTape(tape);
    recognizer->run();
    CHECK(recognizer->getCurrentState() == "reject");
    delete tape;
    delete recognizer;
}

TEST_CASE("TuringMachine::runExecutioner") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
    addOne->setTape(tape);
    addOne->run();
    CHECK(addOne->getCurrentState() == "halt");
    CHECK(tape->toString() == "$ 0 1 0 0");
    delete tape;
    delete addOne;
}

TEST_CASE("TuringMachine::runExecutionerWithHelperMachine") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 1 1 1"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
    addOne->setTape(tape);
    addOne->run();
    CHECK(addOne->getCurrentState() == "halt");
    CHECK(tape->toString() == "$ 1 0 0 0");
    delete tape;
    delete addOne;
}

TEST_CASE("TuringMachine::composition") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* swapDigits = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/swapDigits.txt"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
    swapDigits->setTape(tape);
    swapDigits->composition(addOne);
    CHECK(tape->toString() == "$ 1 0 1 1");
    delete tape;
    delete swapDigits;
    delete addOne;
}

TEST_CASE("TuringMachine::runWhile") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 1 1 1"));
    TuringMachine* notEqualOnesAndZeroes = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/notEqualOnesAndZeroes.txt"));
    TuringMachine* shiftRightBinary = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/shiftRightBinary.txt"));
    notEqualOnesAndZeroes->setTape(tape);
    shiftRightBinary->setTape(tape);
    shiftRightBinary->runWhile(notEqualOnesAndZeroes);
    CHECK(tape->toString() == "$ 0 0 0 1 1 1");
    delete tape;
    delete notEqualOnesAndZeroes;
    delete shiftRightBinary;
}

TEST_CASE("TuringMachine::runAnotherMachineBasedOnCurrentStateIfTrue") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/zero^n_one^n.txt"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
    TuringMachine* swapDigits = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/swapDigits.txt"));
    recognizer->setTape(tape);
    recognizer->runAnotherMachineBasedOnCurrentState(addOne, swapDigits);
    CHECK(tape->toString() == "$ 0 1 0 0");
    delete tape;
    delete recognizer;
    delete addOne;
    delete swapDigits;
}

TEST_CASE("TuringMachine::runAnotherMachineBasedOnCurrentStateIfFalse") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/zero^n_one^n.txt"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/addOne.txt"));
    TuringMachine* swapDigits = new TuringMachine(FileOpener::openFile("/Users/boyan/Desktop/Turing/swapDigits.txt"));
    recognizer->setTape(tape);
    recognizer->runAnotherMachineBasedOnCurrentState(addOne, swapDigits);
    CHECK(tape->toString() == "$ 1 1 0");
    delete tape;
    delete recognizer;
    delete addOne;
    delete swapDigits;
}