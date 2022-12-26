#include <iostream>

#include "Parser.h"
#include "TokenDefinitions.h"

Parser::Parser(std::vector<Token> tokens)
{
	this->position = 0;
	this->errorPosition = -1;
	this->tokens = tokens;

	this->Errors = ErrorHandler();
}

bool Parser::Parse()
{
	bool prog = this->Prog();
	return prog;
}

// <PROG>->PROG id <VAR> begin < LISTST> end
bool Parser::Prog()
{
	auto prog = this->Match(TokenDefs.at(PROGRAM));

	if (!prog)
	{
		this->Errors.Call(ErrorDefs.at(PROGRAM));
		return false;
	}

	auto id = this->Match(TokenDefs.at(IDENTIFIER));
	if (!id)
	{
		this->Errors.Call(ErrorDefs.at(IDENTIFIER));
		return false;
	}

	bool var = this->Var();
	if (!var)
	{
		return false;
	}

	auto begin = this->Match(TokenDefs.at(BEGIN));
	if (!begin)
	{
		this->Errors.Call(ErrorDefs.at(BEGIN));
		return false;
	}

	bool listSt = this->ListSt();
	if (!listSt)
	{
		this->Errors.Call(ErrorDefs.at("Ожидался список команд"));
		return false;
	}

	auto end = this->Match(TokenDefs.at(END));
	if (!end)
	{
		this->Errors.Call(ErrorDefs.at(END));
		return false;
	}

	return true;
}

// <VAR>->VAR < IDLIST> : <TYPE>
bool Parser::Var()
{
	auto var = this->Match(TokenDefs.at(VARIABLE));
	if (!var)
	{
		this->Errors.Call(ErrorDefs.at(VARIABLE));
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
		return false;
	}

	bool type = this->Type();
	if (!type)
	{
		return false;
	}

	return true;
}

// < IDLIST> -> id | < IDLIST>, id
bool Parser::IdList()
{
	auto id = this->Match({ TokenDefs.at(IDENTIFIER), TokenDefs.at(COMMA) });
	if (!id)
	{
		this->Errors.Call(ErrorDefs.at(COMMA));
		return false;
	}

	auto comma = this->Match(TokenDefs.at(COMMA));
	if (comma)
	{
		return this->IdList();
	}

	return true;
}

// <TYPE>-> int | float | bool | string
bool Parser::Type()
{
	auto type = this->Match(TokenDefs.at(TYPE));
	if (!type)
	{
		this->Errors.Call(ErrorDefs.at(TYPE));
		return false;
	}

	return true;
}

// < LISTST>-> < ST> | < LISTST> <ST>
bool Parser::ListSt()
{
	bool st = this->St();
	if (!st)
	{
		return this->St();
	}

	return this->ListSt();
}

// <ST>-> <READ>|<WRITE>| <ASSIGN>
bool Parser::St()
{
	bool read = this->Read();
	bool write = this->Write();

	return read || write;
}

bool Parser::Assign()
{
	auto id = this->Match(TokenDefs.at(IDENTIFIER));
	if (!id)
	{
		this->Errors.Call(ErrorDefs.at(IDENTIFIER));
		this->position -= 1;
		return false;
	}

	auto assign = this->Match(TokenDefs.at(ASSIGN));
	if (!assign)
	{
		this->Errors.Call(ErrorDefs.at(ASSIGN));
		return false;
	}

	bool expression = this->Exp();
	if (!expression)
	{
		return false;
	}

	return true;
}

bool Parser::Exp()
{
	return true;
}

bool Parser::T()
{

	auto mul = this->Match(TokenDefs.at(MUL));
	if (!mul)
	{
		this->Errors.Call(ErrorDefs.at(MUL));
		return false;
	}

	return true;
}

bool Parser::F()
{
	return true;
}

bool Parser::Read()
{
	auto read = this->Match(TokenDefs.at(READ));
	if (!read)
	{
		this->Errors.Call(ErrorDefs.at(READ));
		this->position -= 1;
		return false;
	}

	auto lp = this->Match(TokenDefs.at(LP));
	if (!lp)
	{
		this->Errors.Call(ErrorDefs.at(LP));
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
		this->Errors.Call(ErrorDefs.at(RP));
		return false;
	}

	auto semi = this->Match(TokenDefs.at(SEMICOLON));
	if (!rp)
	{
		this->Errors.Call(ErrorDefs.at(SEMICOLON));
		return false;
	}

	return true;
}

bool Parser::Write()
{
	auto write = this->Match(TokenDefs.at(WRITE));
	if (!write)
	{
		this->Errors.Call(ErrorDefs.at(WRITE));
		this->position -= 1;
		return false;
	}

	auto lp = this->Match(TokenDefs.at(LP));
	if (!lp)
	{
		this->Errors.Call(ErrorDefs.at(LP));
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
		this->Errors.Call(ErrorDefs.at(RP));
		return false;
	}

	auto semi = this->Match(TokenDefs.at(SEMICOLON));
	if (!rp)
	{
		this->Errors.Call(ErrorDefs.at(SEMICOLON));
		return false;
	}

	return true;
}

void Parser::NextPosition()
{
	if (this->position < this->tokens.size() - 1)
	{
		this->position += 1;
	}
}

std::optional<Token> Parser::Match(TokenType type)
{
	Token currentToken = this->tokens.at(this->position);
	this->Errors.SetPosition(currentToken.position);

	if (type.name == currentToken.type.name)
	{
		this->NextPosition();
		return currentToken;
	} 


	//std::cout << currentToken.text << std::endl;
	return std::nullopt;
}

std::optional<Token> Parser::Match(std::vector<TokenType> tokenTypes)
{
	Token currentToken = this->tokens.at(this->position);
	this->Errors.SetPosition(currentToken.position);

	for (TokenType type : tokenTypes)
	{
		if (type.name == currentToken.type.name)
		{
			//std::cout << type.name << " " << currentToken.type.name << std::endl;
			this->NextPosition();
			return currentToken;
		}
	}

	return std::nullopt;
}
