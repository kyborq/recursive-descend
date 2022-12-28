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

string ReadFile(string fileName)
{
    ifstream input(fileName);

    if (!input.is_open())
        return "";

    string result;
    string line;

    while (getline(input, line))
    {
        result += line + " ";
    }

    return result;
}

void WriteFile(string fileName, string text)
{
    ofstream output(fileName);
    
    if (!output.is_open())
        return;

    output << text << endl;
}

bool CheckCode(string code)
{
    Lexer lexer = Lexer(code);
    vector<Token> tokens = lexer.Tokenize();

    if (tokens.size() == 0)
    {
        cout << code.substr(lexer.GetPosition(), 5) << " <- "
            << "синтаксическая ошибка" << endl;
        return false;
    }

    Parser parser = Parser(tokens);
    bool result = parser.Parse();

    return result;
}

struct Args
{
    string fileIn;
    string fileOut;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    Args args;

    if (argc != 3)
    {
        cout << "Не хватает аргументов" << endl;
        return nullopt;
    }

    args.fileIn = argv[1];
    args.fileOut = argv[2];

    return args;
}

int main(int argc, char* argv[])
{
    setlocale(0, "");

    auto args = ParseArgs(argc, argv);
    if (!args)
        return 0;

    string code = ReadFile(args->fileIn);

    bool result = CheckCode(code);

    if (result)
    {
        WriteFile(args->fileOut, "OK!");
    }
    else
    {
        WriteFile(args->fileOut, "FAILED!");
    }
}