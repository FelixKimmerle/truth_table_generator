#pragma once
#include <string>
#include <vector>
#include "Lexer.hpp"
#include <stack>
#include "Stack.hpp"
#include <map>

static const char *OpCodeStrings[] =
    {
        "OP_And",
        "OP_Or",
        "OP_Xor",
        "OP_Eq",
        "OP_Impl",
        "OP_Impl_left",
        "OP_Not",
        "OP_True",
        "OP_False",
        "OP_Load",
        "OP_Return",
};

class Programm
{
public:
    enum OpCode : uint8_t
    {
        OP_And,
        OP_Or,
        OP_Xor,
        OP_Eq,
        OP_Impl,
        OP_Impl_left,
        OP_Not,
        OP_True,
        OP_False,
        OP_Load,
        OP_Return,
    };

private:
    std::vector<uint8_t> m_OpCode;
    void Level0();
    void Level1();
    Lexer m_Lexer;
    std::vector<char> m_Indices;

    std::vector<bool> m_Data;
    bool Add();

    int Stacksize();
    bool available;
    Stack stack;
    bool error;

public:
    Programm(const std::string &source);
    ~Programm();
    bool Execute();
    bool availible();
    std::vector<bool> next();
    std::vector<char> Variables();
    std::vector<uint8_t> GetOpCode();
};
