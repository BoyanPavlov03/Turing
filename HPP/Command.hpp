#pragma once

enum Command {
    LEFT,
    RIGHT,
    STAY
};

static std::string commandToString(Command command) {
    switch (command) {
        case LEFT:
            return "L";
        case RIGHT:
            return "R";
        case STAY:
            return "S";
    }
    return "";
}