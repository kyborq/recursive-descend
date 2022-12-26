#pragma once
#include <string>
#include <regex>

struct TokenType {
    std::string name;
    std::regex type;
};