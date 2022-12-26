#pragma once
#include <string>
#include <vector>
#include <optional>

#include "Token.h"
#include "TokenType.h"
#include "ErrorHandler.h"

class Parser
{
private:
	std::vector<Token> tokens;
	int position;

	bool Prog();
	bool Var();
	bool IdList();
	bool ListSt();
	bool Type();
	bool St();
	bool Assign();
	bool Exp();
	bool T();
	bool F();
	bool Read();
	bool Write();

	void NextPosition();
	std::optional<Token> Match(TokenType);
	std::optional<Token> Match(std::vector<TokenType>);

	int errorPosition;
	ErrorHandler Errors;
public:
	Parser(std::vector<Token>);
	bool Parse();
};

