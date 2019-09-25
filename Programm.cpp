#include "Programm.hpp"
#include <iostream>
#include <algorithm>
#include "Stack.hpp"
Programm::Programm(const std::string &source) : m_Lexer(source)
{
    do
    {
        m_Lexer.getNext();
        Level0();
        m_OpCode.push_back(OP_Return);
    } while (m_Lexer.getCurrent().getType() == Token::T_Push);

}

Programm::~Programm()
{
}



std::vector<uint8_t> Programm::GetOpCode()
{
    return m_OpCode;
}

void Programm::Level0()
{
    Level1();
    bool w = true;
    while (w)
    {
        switch (m_Lexer.getCurrent().getType())
        {
        case Token::T_And:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_And);
            break;
        case Token::T_Or:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_Or);
            break;
        case Token::T_Not:
            m_OpCode.push_back(OP_Not);
            m_Lexer.getNext();
            break;
        case Token::T_Equal:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_Eq);
            break;
        case Token::T_NEqual:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_Eq);
            m_OpCode.push_back(OP_Not);
            break;
        case Token::T_Xor:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_Xor);
            break;
        case Token::T_Impl:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_Impl);
            break;

        case Token::T_Impl_left:
            m_Lexer.getNext();
            Level1();
            m_OpCode.push_back(OP_Impl_left);
            break;

        default:
            w = false;
            break;
        }
    }
}
void Programm::Level1()
{
    switch (m_Lexer.getCurrent().getType())
    {
    case Token::T_Variable:
    {
        m_OpCode.push_back(OP_Load);
        auto item = std::find(m_Indices.begin(), m_Indices.end(), m_Lexer.getCurrent().getCharacter());
        if (item == m_Indices.end())
        {
            m_Indices.push_back(m_Lexer.getCurrent().getCharacter());
            m_OpCode.push_back(m_Indices.size() - 1);
        }
        else
        {
            m_OpCode.push_back(std::distance(m_Indices.begin(), item));
        }
        m_Lexer.getNext();
    }
    break;
    case Token::T_True:
        m_OpCode.push_back(OP_True);
        m_Lexer.getNext();

        break;
    case Token::T_False:
        m_OpCode.push_back(OP_False);
        m_Lexer.getNext();

        break;
    case Token::T_BracketOpen:
        m_Lexer.getNext();
        Level0();
        m_Lexer.getNext();
        break;
    case Token::T_Not:
        m_Lexer.getNext();
        Level1();
        m_OpCode.push_back(OP_Not);
        break;

    default:
        break;
    }
}

int Programm::Stacksize()
{
    unsigned int size = 0;
    unsigned int maxsize = 0;
    for (unsigned int x = 0; x < m_OpCode.size(); x++)
    {
        switch (m_OpCode[x])
        {
        case OP_Load:
            size++;
            x++;
            break;
        case OP_False:
        case OP_True:
            size++;
            break;
        case OP_Or:
        case OP_Xor:
        case OP_And:
        case OP_Eq:
        case OP_Return:
        case OP_Impl:
        case OP_Impl_left:
            size--;
            break;

        default:
            break;
        }
        if (size > maxsize)
        {
            maxsize = size;
        }
    }
    return maxsize;
}

bool Programm::Add()
{
    bool uebertrag = true;
    if (!m_Data[m_Data.size() - 1])
    {
        m_Data[m_Data.size() - 1] = 1;
        return true;
    }
    m_Data[m_Data.size() - 1] = 0;

    for (int i = m_Data.size() - 2; i >= 0; i--)
    {
        if (uebertrag)
        {
            uebertrag = m_Data[i];
            m_Data[i] = !m_Data[i];
        }
        else
        {
            return true;
        }
    }
    return !uebertrag;
}

bool Programm::availible()
{
    return available;
}

std::vector<char> Programm::Variables()
{
    return m_Indices;
}

std::vector<bool> Programm::next()
{
    std::vector<bool> result;
    for (auto &&i : m_Data)
    {
        result.push_back(i);
    }

    for (unsigned int x = 0; x < m_OpCode.size(); x++)
    {
        switch (m_OpCode[x])
        {
        case OP_Load:
        {
            stack.push(m_Data[m_OpCode[++x]]);
            break;
        }
        case OP_Not:
        {
            bool value = stack.top();
            stack.pop();
            stack.push(!value);
        }
        break;
        case OP_False:
            stack.push(false);
            break;
        case OP_True:
            stack.push(true);
            break;
        case OP_Return:
            result.push_back(stack.top());
            stack.pop();
            break;
        case OP_Or:
        {
            bool top = stack.top();
            stack.pop();
            bool bottom = stack.top();
            stack.pop();
            stack.push(top || bottom);
            break;
        }
        case OP_Xor:
        {
            bool top = stack.top();
            stack.pop();
            bool bottom = stack.top();
            stack.pop();
            stack.push(top ^ bottom);
            break;
        }
        case OP_And:
        {
            bool top = stack.top();
            stack.pop();
            bool bottom = stack.top();
            stack.pop();
            stack.push(top && bottom);
            break;
        }
        case OP_Eq:
        {
            bool top = stack.top();
            stack.pop();
            bool bottom = stack.top();
            stack.pop();
            stack.push(top == bottom);
            break;
        }
        case OP_Impl:
        {
            bool top = stack.top();
            stack.pop();
            bool bottom = stack.top();
            stack.pop();
            stack.push(!(!top && bottom));
            break;
        }
        case OP_Impl_left:
        {
            bool top = stack.top();
            stack.pop();
            bool bottom = stack.top();
            stack.pop();
            stack.push(!(!bottom && top));
            break;
        }
        default:
            break;
        }
    }
    available = Add();
    return result;
}

void Programm::Execute()
{
    m_Data.resize(m_Indices.size(), false);
    available = true;
    stack.resize(Stacksize());
}