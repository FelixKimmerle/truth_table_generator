#pragma once
#include "Token.hpp"
#include <string>
class Lexer
{
private:
    std::string m_Src;
    Token m_Current;
    unsigned int m_uiPos;
    void PushToken(Token::TokenType type);
public:
    Lexer(const std::string & p_Src);
    ~Lexer();
    Token &getNext();
    Token &getCurrent();
};
