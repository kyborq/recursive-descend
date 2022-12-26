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

	std::optional<Token> Match(TokenType);
	bool IsMatch(TokenType);
	std::optional<Token> MatchAny(std::vector<TokenType>);

	bool Prog();
	bool Var();
	bool Type();
	bool IdList();

	bool ListSt();
	bool St();

	bool Write();
	bool Read();

	bool Assign();
	bool Exp();
	bool T();
	bool F();

	bool isError;
	ErrorHandler error;
public:
	Parser(std::vector<Token>);
	bool Parse();
};

