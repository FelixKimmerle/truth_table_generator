#include "Lexer.hpp"

Lexer::Lexer(const std::string &p_Src) : m_Src(p_Src), m_uiPos(0)
{
}

Lexer::~Lexer()
{
}

void Lexer::PushToken(Token::TokenType type)
{
    m_Current = Token(type, m_Src[m_uiPos]);
}

Token &Lexer::getNext()
{
    if (m_uiPos < m_Src.size())
    {
        switch (m_Src[m_uiPos])
        {
        case '0':
            PushToken(Token::T_False);
            break;
        case '1':
            PushToken(Token::T_True);
            break;
        case '=':
            PushToken(Token::T_Equal);
            break;
        case '&':
            PushToken(Token::T_And);
            break;
        case '|':
            PushToken(Token::T_Or);
            break;
        case '(':
            PushToken(Token::T_BracketOpen);
            break;
        case ')':
            PushToken(Token::T_BracketClose);
            break;
        case '^':
            PushToken(Token::T_Xor);
            break;
        case '!':
            if (m_uiPos + 1 < m_Src.size())
            {
                if (m_Src[m_uiPos + 1] == '=')
                {
                    PushToken(Token::T_NEqual);
                    m_uiPos++;
                    break;
                }
            }
            PushToken(Token::T_Not);

            break;
        case '-':
            if (m_uiPos + 1 < m_Src.size())
            {
                if (m_Src[m_uiPos + 1] == '>')
                {
                    PushToken(Token::T_Impl);
                    m_uiPos++;
                    break;
                }
            }
            break;
        case ',':
            PushToken(Token::T_Push);
            break;

        case '<':
            if (m_uiPos + 1 < m_Src.size())
            {
                if (m_Src[m_uiPos + 1] == '-')
                {
                    PushToken(Token::T_Impl_left);
                    m_uiPos++;
                    break;
                }
            }
        case '>':
        case ' ':
            m_uiPos++;
            return getNext();
            break;
        default:
            PushToken(Token::T_Variable);

            break;
        }
    }
    else
    {
        m_Current = Token(Token::T_EOF, ' ');
    }
    m_uiPos++;
    return m_Current;
}

Token &Lexer::getCurrent()
{
    return m_Current;
}