#ifndef VALUE_H
#define VALUE_H

#include <iostream>

#include <vector>

class Value
{
public:
    // constructors
    Value(
        double data,
        std::vector<Value *> children = {},
        std::string op = "")
        : m_data(data),
          m_grad(0.0),
          _prev(children),
          _op(op) {}

    // methods
    // op
    Value *operator+(Value &other); // add
    Value *operator*(Value &other); // mult
    // helpers
    void print() const
    {
        std::cout << "Value(data=" << m_data << ", grad=" << m_grad << ")" << std::endl;
    }

    double m_data;              // the number
    double m_grad;              // derivative
    std::vector<Value *> _prev; // points to the parents
    std::string _op;            // hold operators, for debugging
private:
};

#endif