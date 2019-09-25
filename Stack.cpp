#include "Stack.hpp"

Stack::Stack(unsigned int size)
{
    pos = 0;
    msize = size;
    mem = new bool[size];
}
Stack::Stack()
{
    mem = nullptr;
    pos = 0;
    msize = 0;
}

Stack::~Stack()
{
    delete[] mem;
    mem = nullptr;
}

void Stack::resize(unsigned int size)
{
    if (mem == nullptr)
    {
        delete[] mem;
    }
    msize = size;
    mem = new bool[size];
}

bool &Stack::top()
{
    return mem[pos - 1];
}
void Stack::pop()
{
    pos--;
}
void Stack::push(const bool x)
{
    mem[pos++] = x;
}

void Stack::poppush(bool x)
{
    mem[pos - 1] = x;
}
void Stack::Print()
{
    std::cout << "------------------" << std::endl;
    for (unsigned int i = 0; i < msize; i++)
    {
        std::cout << mem[i] << std::endl;
    }
}