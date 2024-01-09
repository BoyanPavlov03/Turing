#pragma once
#include <fstream>
#include <string>
#include <sstream>

struct FileOpener {
    static std::ifstream openFile(const std::string& fileName);
    static std::ifstream createStreamFrom(const std::string& input);
};