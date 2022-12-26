#pragma once
#include <string>
#include "TokenType.h"

struct Token {
    int position;
    std::string text;
    TokenType type;
};
