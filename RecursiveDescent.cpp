#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <vector>
#include <locale>
#include <fstream>

#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "TokenType.h"

using namespace std;

string Spaces(int amount)
{
    string result;

    for (int i = 0; i < amount; i++)
        result += " ";

    return result;
}

vector<string> File2Vector(string fileName)
{
    ifstream input(fileName);
    vector<string> result;
    string line;

    while (getline(input, line))
    {
        result.push_back(line);
    }

    return result;
}

string File2Line(string fileName)
{
    ifstream input(fileName);
    string result;
    string line;

    while (getline(input, line))
    {
        result += line + " ";
    }

    return result;
}

int main(int argc, char* argv[])
{
    setlocale(0, "");

    string code = "PROG id VAR id, id: int BEGIN WRITE(id); READ (id); END";


    Lexer lexer = Lexer(code);
    vector<Token> tokens = lexer.Tokenize();

    cout << code << endl;

    if (tokens.size() == 0)
    {
        cout << Spaces(lexer.GetPosition())
            << "^ ошибка в синтаксисе" << endl << endl;
        return 0;
    }

    Parser parser = Parser(tokens);
    bool q = parser.Parse();

    if (q)
    {
        cout << "OK!";
    }
    else
    {
        cout << "BAD!!!";
    }
}