#pragma once
#include <string>
#include <list>
#include <iostream>
#include <regex>
#include <vector>
#include <optional>

#include "TokenType.h"
#include "Token.h"

class Lexer
{
private:
	std::vector<Token> tokens;
	std::string code;
	int position;
	
	bool NextToken(int);
	std::optional<Token> FindToken(TokenType, std::string);
public:
	Lexer(std::string);
	std::vector<Token> Tokenize();
	int GetPosition();
};

