#include "value.hpp"

#include <cmath>

ValuePtr operator+(ValuePtr parent1, ValuePtr parent2)
{
    ValuePtr out = std::make_shared<Value>(parent1->_data + parent2->_data);

    out->_prev = {parent1, parent2};
    out->_op = "+";

    out->_backward = [parent1, parent2, out]()
    {
        parent1->_grad += out->_grad * 1.0;
        parent2->_grad += out->_grad * 1.0;
    };

    return out;
}

ValuePtr operator-(ValuePtr parent1, ValuePtr parent2)
{
    ValuePtr out = std::make_shared<Value>(parent1->_data - parent2->_data);

    out->_prev = {parent1, parent2};
    out->_op = "-";

    out->_backward = [parent1, parent2, out]()
    {
        parent1->_grad += out->_grad * 1.0;
        parent2->_grad += out->_grad * -1.0;
    };
    return out;
}

ValuePtr operator*(ValuePtr parent1, ValuePtr parent2)
{
    ValuePtr out = std::make_shared<Value>(parent1->_data * parent2->_data);

    out->_prev = {parent1, parent2};
    out->_op = "*";

    out->_backward = [parent1, parent2, out]()
    {
        parent1->_grad += out->_grad * parent2->_data;
        parent2->_grad += out->_grad * parent1->_data;
    };
    return out;
}

ValuePtr operator/(ValuePtr parent1, ValuePtr parent2)
{
    return parent1 * valuePow(parent2, -1.0);
}

ValuePtr valuePow(ValuePtr parent1, double exp)
{
    ValuePtr out = std::make_shared<Value>(pow(parent1->_data, exp));

    out->_prev = {parent1};
    out->_op = "^";

    out->_backward = [parent1, exp, out]()
    {
        parent1->_grad += pow(parent1->_data, exp - 1) * exp * out->_grad;
    };

    return out;
}