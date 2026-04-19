#include "value.hpp"

#include <set>
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

ValuePtr valueTanh(ValuePtr parent)
{
    ValuePtr out = std::make_shared<Value>(std::tanh(parent->_data));

    out->_prev = {parent};
    out->_op = "tanh";

    out->_backward = [parent, out]()
    {
        double local_derivative = 1 - (out->_data * out->_data); // out->_data = tanh(x)
        parent->_grad = out->_grad * local_derivative;
    };
    return out;
}

void Value::backward()
{
    std::vector<ValuePtr> topo;
    std::set<Value *> visited;

    std::function<void(ValuePtr)> build_topo = [&](ValuePtr v)
    {
        if (visited.find(v.get()) == visited.end())
        {
            visited.insert(v.get());
            for (auto parent : v->_prev)
            {
                build_topo(parent);
            }
            topo.push_back(v);
        }
    };
    build_topo(shared_from_this());
    this->_grad = 1.0;
    for (auto it = topo.rbegin(); it != topo.rend(); it++)
    {
        (*it)->_backward();
    }
}