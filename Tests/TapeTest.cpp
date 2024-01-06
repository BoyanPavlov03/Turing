#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"
#include "../HPP/Tape.hpp"
#include "../HPP/FileOpener.hpp"

TEST_CASE("TapeNode") {
    TapeNode* node = new TapeNode("a", "a", nullptr, nullptr);
    CHECK(node->dataForWrite == "a");
    CHECK(node->tempData == "a");
    CHECK(node->next == nullptr);
    CHECK(node->prev == nullptr);
    delete node;
}

TEST_CASE("TapeStartingWith$") {
    Tape* tape = new Tape(FileOpener::createStreamFrom("$ 0 0 1"));
    CHECK(tape->head->dataForWrite == "$");
    CHECK(tape->head->next->dataForWrite == "0");
    CHECK(tape->head->next->next->dataForWrite == "0");
    CHECK(tape->head->next->next->next->dataForWrite == "1");
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