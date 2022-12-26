#include "Lexer.h"
#include "TokenDefinitions.h"

Lexer::Lexer(std::string code)
{
    this->position = 0;
    this->code = code;
}

std::optional<Token> Lexer::FindToken(TokenType type, std::string code)
{
    std::smatch match;
    bool result = std::regex_search(code, match, type.type);

    if (result)
    {
        int position = match.position();
        int length = match.length();
        std::string word = code.substr(position, length);
        Token token = { position, word, type };

        return token;
    }

    return std::nullopt;
}

bool Lexer::NextToken(int position)
{
    if (position >= this->code.size())
    {
        return true;
    }

    std::string code = this->code.substr(position);
    int offset = position;

    for (auto const& [key, type] : TokenDefs)
    {
        auto token = FindToken(type, code);
        
        if (token)
        {
            if (token->type.name != SPACE)
            {
                token->position = position;
                this->tokens.push_back(token.value());
            }
            offset = token->text.length();
            return NextToken(position + offset);
        }
    }

    this->position = position;
    
    return false;
}

std::vector<Token> Lexer::Tokenize()
{
    bool success = this->NextToken(this->position);
    if (!success)
    {
        return {};
    }

    return this->tokens;
}

int Lexer::GetPosition()
{
    return this->position;
}
