#include "../HPP/FileOpener.hpp"

std::ifstream FileOpener::openFile(const std::string& fileName) {
    std::ifstream file("../Resources/" + fileName + ".txt");
    if (!file.is_open()) {
        throw std::invalid_argument("File not found");
    }
    return file;
}

std::ifstream FileOpener::createStreamFrom(const std::string& input) {
    std::istringstream inputStringStream(input);
    std::ifstream stream;
    stream.basic_ios<char>::rdbuf(inputStringStream.rdbuf());
    return stream;
}