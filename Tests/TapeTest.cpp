#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"
#include "../HPP/Tape.hpp"
#include "../HPP/FileOpener.hpp"

TEST_CASE("TapeStartingWith$") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1"));
    CHECK(tape->toString() == "$ 0 0 1");
    delete tape;
}

TEST_CASE("TapeStartingWithout$") {
    try {
        Tape* tape = new Tape(FileOpener::createStreamFrom("0 0 1"));
        delete tape;
    } catch (std::invalid_argument& e) {
        CHECK(e.what() == std::string("The tape must start with $"));
    }
}