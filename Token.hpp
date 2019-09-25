#pragma once
#include <stdint.h>
#include <ostream>

class Token
{
public:
    enum TokenType : int8_t
    {
        T_ERROR,
        T_BracketClose,
        T_BracketOpen,
        T_True,
        T_False,
        T_Or,
        T_And,
        T_Xor,
        T_Not,
        T_Impl,
        T_Impl_left,
        T_Equal,
        T_NEqual,
        T_Variable,
        T_EOF,
        T_Push,
    };

private:
    char m_Character;
    TokenType m_Type;

public:
    Token(TokenType p_Type, char p_Character);
    Token();
    ~Token();
    TokenType getType();
    char getCharacter();

    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};
