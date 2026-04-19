#ifndef VALUE_HPP
#define VALUE_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <functional>
#include <string>

class Value : public std::enable_shared_from_this<Value>
{
public:
    Value(double data) : _data(data), _op(""), _grad(0.0), _backward([]() {}) {}

    void backward();

    double _data;
    std::string _op;
    double _grad;
    std::vector<std::shared_ptr<Value>> _prev;
    std::function<void()> _backward;
};

using ValuePtr = std::shared_ptr<Value>;

ValuePtr operator+(ValuePtr parent1, ValuePtr parent2);
ValuePtr operator-(ValuePtr parent1, ValuePtr parent2);
ValuePtr operator*(ValuePtr parent1, ValuePtr parent2);
ValuePtr operator/(ValuePtr parent1, ValuePtr parent2);
ValuePtr valuePow(ValuePtr parent, double exponent);
ValuePtr valueTanh(ValuePtr parent);

#endif