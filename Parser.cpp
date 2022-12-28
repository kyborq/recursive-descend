#include <iostream>

#include "Parser.h"
#include "TokenDefinitions.h"

Parser::Parser(std::vector<Token> tokens)
{
	this->position = 0;
	this->isError = false;
	this->tokens = tokens;
}

bool Parser::Parse()
{
	bool prog = this->Prog();
	return prog;
}


std::optional<Token> Parser::Match(TokenType type)
{
	Token currentToken = this->tokens.at(this->position);

	if (type.name == currentToken.type.name)
	{
		if (this->position < this->tokens.size() - 1)
		{
			this->position += 1;
		}

		return currentToken;
	} 

	this->error.SetPosition(currentToken.position);
	return std::nullopt;
}

bool Parser::IsMatch(TokenType type)
{
	Token currentToken = this->tokens.at(this->position);
	bool isMatching = type.name == currentToken.type.name;

	if (isMatching)
	{
		if (this->position < this->tokens.size() - 1)
		{
			this->position += 1;
		}
	}

	this->error.SetPosition(currentToken.position);
	return isMatching;
}

std::optional<Token> Parser::MatchAny(std::vector<TokenType> types)
{

	Token currentToken = this->tokens.at(this->position);

	for (TokenType type : types)
	{

		bool isMatching = type.name == currentToken.type.name;

		if (isMatching)
		{
			if (this->position < this->tokens.size() - 1)
			{
				this->position += 1;
			}
			return currentToken;
		}

	}

	this->error.SetPosition(currentToken.position);

	return std::nullopt;
}

bool Parser::Prog()
{
	auto prog = this->Match(TokenDefs.at(PROGRAM));
	if (!prog)
	{
		this->error.Call(ErrorDefs.at(PROGRAM));
		return false;
	}

	auto id = this->Match(TokenDefs.at(IDENTIFIER));
	if (!id)
	{
		this->error.Call(ErrorDefs.at(IDENTIFIER));
		return false;
	}

	bool var = this->Var();
	if (!var) {
		return false;
	}

	auto begin = this->Match(TokenDefs.at(BEGIN));
	if (!begin)
	{
		this->error.Call(ErrorDefs.at(BEGIN));
		return false;
	}

	bool listSt = this->ListSt();
	if (!listSt)
	{
		return false;
	}

	auto end = this->Match(TokenDefs.at(END));
	if (!end)
	{
		this->error.Call(ErrorDefs.at(END));
		return false;
	}

	return true;
}

bool Parser::Var()
{
	auto var = this->Match(TokenDefs.at(VARIABLE));
	if (!var)
	{
		this->error.Call(ErrorDefs.at(VARIABLE));
		return false;
	}

	bool idList = this->IdList();
	if (!idList)
	{
		return false;
	}


	auto colon = this->Match(TokenDefs.at(COLON));
	if (!colon)
	{
		this->error.Call(ErrorDefs.at(COLON));
		return false;
	}

	bool type = this->Type();
	if (!type)
	{
		return false;
	}

	auto semi = this->Match(TokenDefs.at(SEMICOLON));
	if (!semi)
	{
		this->error.Call(ErrorDefs.at(SEMICOLON));
		return false;
	}

	return true;
}

bool Parser::Type()
{
	auto type = this->Match(TokenDefs.at(TYPE));
	if (!type)
	{
		this->error.Call(ErrorDefs.at(TYPE));
		return false;
	}

	return true;
}

bool Parser::IdList()
{
	auto id = this->Match(TokenDefs.at(IDENTIFIER));
	if (!id)
	{
		this->error.Call(ErrorDefs.at(IDENTIFIER));
		return false;
	}

	bool comma = this->IsMatch(TokenDefs.at(COMMA));
	if (comma)
	{
		return this->IdList();
	}

	return true;
}

bool Parser::ListSt()
{
	bool st = this->St();
	if (!st)
	{
		return true;
	}
	else
	{
		return this->ListSt();
	}

	return false;
}

bool Parser::St()
{
	auto op = this->MatchAny({ 
		TokenDefs.at(WRITE), 
		TokenDefs.at(READ), 
		TokenDefs.at(IDENTIFIER) 
	});

	if (!op)
	{
		return false;
	}

	this->position -= 1;

	if (op->type.name == TokenDefs.at(WRITE).name)
	{
		bool write = this->Write();
		if (!write)
		{
			return false;
		}
	}

	if (op->type.name == TokenDefs.at(READ).name)
	{
		bool read = this->Read();
		if (!read)
		{
			return false;
		}
	}

	if (op->type.name == TokenDefs.at(IDENTIFIER).name)
	{
		bool assign = this->Assign();
		if (!assign)
		{
			return false;
		}
	}

	return true;
}

bool Parser::Write()
{
	auto write = this->Match(TokenDefs.at(WRITE));
	if (!write)
	{
		this->error.Call(ErrorDefs.at(WRITE));
		return false;
	}

	auto lp = this->Match(TokenDefs.at(LP));
	if (!lp)
	{
		this->error.Call(ErrorDefs.at(LP));
		return false;
	}

	bool idList = this->IdList();
	if (!idList)
	{
		return false;
	}

	auto rp = this->Match(TokenDefs.at(RP));
	if (!rp)
	{
		this->error.Call(ErrorDefs.at(RP));
		return false;
	}

	auto semi = this->Match(TokenDefs.at(SEMICOLON));
	if (!semi)
	{
		this->error.Call(ErrorDefs.at(SEMICOLON));
		return false;
	}

	return true;
}

bool Parser::Read()
{
	auto write = this->Match(TokenDefs.at(READ));
	if (!write)
	{
		this->error.Call(ErrorDefs.at(READ));
		return false;
	}

	auto lp = this->Match(TokenDefs.at(LP));
	if (!lp)
	{
		this->error.Call(ErrorDefs.at(LP));
		return false;
	}

	bool idList = this->IdList();
	if (!idList)
	{
		return false;
	}

	auto rp = this->Match(TokenDefs.at(RP));
	if (!rp)
	{
		this->error.Call(ErrorDefs.at(RP));
		return false;
	}

	auto semi = this->Match(TokenDefs.at(SEMICOLON));
	if (!semi)
	{
		this->error.Call(ErrorDefs.at(SEMICOLON));
		return false;
	}

	return true;
}

bool Parser::Assign()
{
	// id
	auto id = this->Match(TokenDefs.at(IDENTIFIER));
	if (!id)
	{
		this->error.Call(ErrorDefs.at(IDENTIFIER));
		return false;
	}

	// :=
	auto assign = this->Match(TokenDefs.at(ASSIGN));
	if (!assign)
	{
		this->error.Call(ErrorDefs.at(ASSIGN));
		return false;
	}

	// <EXP>
	bool exp = this->Exp();
	if (!exp)
	{
		return false;
	}

	auto semi = this->Match(TokenDefs.at(SEMICOLON));
	if (!semi)
	{
		this->error.Call(ErrorDefs.at(SEMICOLON));
		return false;
	}

	return true;
}

// < EXP> ->  < EXP> + <T> | <T>
bool Parser::Exp()
{
	bool t = this->T();
	if (!t)
	{
		return false;
	}

	auto sum = this->Match(TokenDefs.at(SUM));
	if (sum)
	{
		return this->Exp();
	}

	return true;
}

// <T> -> <T>*<F> | <F>
bool Parser::T()
{
	bool f = this->F();
	if (!f)
	{
		return false;
	}

	auto mul = this->Match(TokenDefs.at(MUL));
	if (mul)
	{
		return this->T();
	}

	return true;
}

// <F>-> -<F>| (<EXP>)| id|num
bool Parser::F()
{
	auto idOrNum = this->MatchAny({ TokenDefs.at(IDENTIFIER), TokenDefs.at(NUMBER) });
	if (idOrNum)
	{
		return true;
	}

	auto lp = this->Match(TokenDefs.at(LP));
	if (lp)
	{
		bool exp = this->Exp();
		if (!exp)
		{
			return false;
		}

		auto rp = this->Match(TokenDefs.at(RP));
		if (rp)
		{
			return true;
		}

		return false;
	}

	auto minus = this->Match(TokenDefs.at(SUB));
	if (minus)
	{
		return this->F();
	}

	return false;
}
