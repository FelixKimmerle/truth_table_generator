#pragma once
#include <iostream>

class Stack
{
  private:
    bool *mem;
    unsigned int pos;
    unsigned int msize;

  public:
    Stack(unsigned int size);
    Stack();
    ~Stack();
    void resize(unsigned int size);
    bool &top();
    void pop();
    void push(bool x);
    void poppush(bool x);
    void Print();
};