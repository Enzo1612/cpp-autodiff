#include "../include/autodiff/value.hpp"

Value *Value::operator+(Value &other)
{
    double result = this->m_data + other.m_data;

    // new to allocate on the heap, before I was creating dangling memory, if parents get deleted, children points to garbage
    Value *out = new Value(result, {this, &other}, "+");

    return out;
}

Value *Value::operator*(Value &other)
{
    double result = this->m_data * other.m_data;

    Value *out = new Value(result, {this, &other}, "*");

    return out;
}