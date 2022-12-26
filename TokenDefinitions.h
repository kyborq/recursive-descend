#pragma once
#include <string>
#include <map>
#include <regex>
#include "TokenType.h"

const std::string PROGRAM = "PROGRAM";
const std::string IDENTIFIER = "IDENTIFIER";
const std::string VARIABLE = "VARIABLE";
const std::string SEMICOLON = "SEMICOLON";
const std::string COLON = "COLON";
const std::string COMMA = "COMMA";
const std::string SPACE = "SPACE";
const std::string LP = "LP";
const std::string RP = "RP";
const std::string BEGIN = "BEGIN";
const std::string END = "END";
const std::string ASSIGN = "ASSIGN";
const std::string SUM = "SUM";
const std::string SUB = "SUB";
const std::string MUL = "MUL";
const std::string NL = "NL";
const std::string TYPE = "TYPE";
const std::string WRITE = "WRITE";
const std::string READ = "READ";
const std::string NUMBER = "num";

const std::map<std::string, TokenType> TokenDefs{
    { PROGRAM, {PROGRAM, std::regex("^PROG\\b")} },
    { IDENTIFIER, {IDENTIFIER, std::regex("^id\\b")}},
    { VARIABLE, {VARIABLE, std::regex("^VAR\\b")}},
    { SEMICOLON, {SEMICOLON, std::regex("^;")}},
    { COLON, {COLON, std::regex("^:")}},
    { COMMA, {COMMA, std::regex("^,")}},
    { SPACE, {SPACE, std::regex("^ ")}},
    { LP, {LP, std::regex("^\\(")}},
    { RP, {RP, std::regex("^\\)")}},
    { BEGIN, {BEGIN, std::regex("^BEGIN\\b")}},
    { END, {END, std::regex("^END\\b")}},
    { ASSIGN, {ASSIGN, std::regex("^:=")}},
    { SUM, {SUM, std::regex("^\\+")}},
    { SUB, {SUB, std::regex("^-")}},
    { MUL, {MUL, std::regex("^\\*")}},
    { NL, {NL, std::regex("^\\n|\\r")}},
    { TYPE, {TYPE, std::regex("^(int|float|bool|string)")}},
    { WRITE, {WRITE, std::regex("^WRITE\\b")}},
    { READ, {READ, std::regex("^READ\\b")}},
    { NUMBER, {NUMBER, std::regex("^num\\b")}},
};

const std::map<std::string, std::string> ErrorDefs{
    { PROGRAM, "Дибила кусок уйди с компьютеру"},
    { IDENTIFIER,"Идентификатор не найден"},
    { VARIABLE, "Отсутствует раздел переменных"},
    { SEMICOLON, "Пропущена точка с запятой [;]"},
    { COLON, "Пропущено двоеточие [:]"},
    { COMMA, "Пропущена запятая [,]"},
    { LP,"Пропущена левая круглая скобка: [(]"},
    { RP,"Пропущена правая круглая скобка: [)]"},
    { BEGIN,"Начало программы не определено: [BEGIN]"},
    { END, "Конец программы не найден: [END]"},
    { ASSIGN,"Не найдено присваивание для выражения: [:=]"},
    { SUM, "Возможно не хватает: [+]"},
    { SUB, "Возможно не хватает: [-]"},
    { MUL, "Возможно не хватает: [*]"},
    { TYPE, "Отсутствует тип переменной(-ых)"},
    { WRITE, "Неправильно записана команда: [WRITE]"},
    { READ, "Неправильно записана команда: [READ]"},
    { NUMBER, "Ожидался Num"},
};
