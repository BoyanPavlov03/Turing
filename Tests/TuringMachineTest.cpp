#include "../doctest.h"
#include "../HPP/Tape.hpp"
#include "../HPP/TuringMachine.hpp"
#include "../HPP/FileOpener.hpp"

TEST_CASE("TuringMachine::runRecognizer") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("zero^n_one^n"));
    recognizer->setTape(tape);
    recognizer->run();
    CHECK(recognizer->getCurrentState() == "accept");
    delete tape;
    delete recognizer;
}

TEST_CASE("TuringMachine::runRecognizerAndReject") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("zero^n_one^n"));
    recognizer->setTape(tape);
    recognizer->run();
    CHECK(recognizer->getCurrentState() == "reject");
    delete tape;
    delete recognizer;
}

TEST_CASE("TuringMachine::runExecutioner") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("addOne"));
    addOne->setTape(tape);
    addOne->run();
    CHECK(addOne->getCurrentState() == "halt");
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 0 1 0 0");
    delete tape;
    delete addOne;
}

TEST_CASE("TuringMachine::runExecutionerWithHelperMachine") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 1 1 1"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("addOne"));
    addOne->setTape(tape);
    addOne->run();
    CHECK(addOne->getCurrentState() == "halt");
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 1 0 0 0");
    delete tape;
    delete addOne;
}

TEST_CASE("TuringMachine::composition") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* swapDigits = new TuringMachine(FileOpener::openFile("swapDigits"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("addOne"));
    swapDigits->setTape(tape);
    swapDigits->composition(addOne);
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 1 0 1 1");
    delete tape;
    delete swapDigits;
    delete addOne;
}

TEST_CASE("TuringMachine::runWhile") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 1 1 1"));
    TuringMachine* notEqualOnesAndZeroes = new TuringMachine(FileOpener::openFile("notEqualOnesAndZeroes"));
    TuringMachine* shiftRightBinary = new TuringMachine(FileOpener::openFile("shiftRightBinary"));
    notEqualOnesAndZeroes->setTape(tape);
    shiftRightBinary->setTape(tape);
    shiftRightBinary->runWhile(notEqualOnesAndZeroes);
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 0 0 0 1 1 1");
    delete tape;
    delete notEqualOnesAndZeroes;
    delete shiftRightBinary;
}

TEST_CASE("TuringMachine::runAnotherMachineBasedOnCurrentStateIfTrue") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("zero^n_one^n"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("addOne"));
    TuringMachine* swapDigits = new TuringMachine(FileOpener::openFile("swapDigits"));
    recognizer->setTape(tape);
    recognizer->runAnotherMachineBasedOnCurrentState(addOne, swapDigits);
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 0 1 0 0");
    delete tape;
    delete recognizer;
    delete addOne;
    delete swapDigits;
}

TEST_CASE("TuringMachine::runAnotherMachineBasedOnCurrentStateIfFalse") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1"));
    TuringMachine* recognizer = new TuringMachine(FileOpener::openFile("zero^n_one^n"));
    TuringMachine* addOne = new TuringMachine(FileOpener::openFile("addOne"));
    TuringMachine* swapDigits = new TuringMachine(FileOpener::openFile("swapDigits"));
    recognizer->setTape(tape);
    recognizer->runAnotherMachineBasedOnCurrentState(addOne, swapDigits);
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 1 1 0");
    delete tape;
    delete recognizer;
    delete addOne;
    delete swapDigits;
}

TEST_CASE("TuringMachine::nondeterministicExample") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 0"));
    TuringMachine* nonDeterministic = new TuringMachine(FileOpener::openFile("nondeterministicExample"));
    nonDeterministic->setTape(tape);
    nonDeterministic->run();
    delete tape;
    tape = new Tape(FileOpener::openFile("outputTape"));
    CHECK(tape->toString() == "$ 1 3 1 $ 2 3 1");
    delete tape;
    delete nonDeterministic;
}