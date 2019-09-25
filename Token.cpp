#include "Token.hpp"

Token::Token(TokenType p_Type, char p_Character) : m_Type(p_Type), m_Character(p_Character)
{
}

Token::Token() : m_Type(T_ERROR), m_Character(' ')
{
}

Token::~Token()
{
}

Token::TokenType Token::getType()
{
    return m_Type;
}
char Token::getCharacter()
{
    return m_Character;
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << "Token (" << token.m_Type << ")"
       << " = " << token.m_Character;
    return os;
}