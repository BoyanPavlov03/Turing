#pragma once
#include <fstream>
#include <string>
#include <sstream>

struct FileOpener {
    static std::ifstream openFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::invalid_argument("File not found");
        }
        return file;
    }

    static std::ifstream createStreamFrom(const std::string& input) {
        std::istringstream inputStringStream(input);
        std::ifstream stream;
        stream.basic_ios<char>::rdbuf(inputStringStream.rdbuf());
        return stream;
    }
};