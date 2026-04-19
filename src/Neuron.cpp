#include "Neuron.hpp"

Neuron::Neuron(int nin)
{
    this->_b = std::make_shared<Value>(random_double());
    for (int i = 0; i < nin; i++)
    {
        this->_w.push_back(std::make_shared<Value>(random_double()));
    };
}
ValuePtr Neuron::operator()(const std::vector<ValuePtr> &x)
{
    ValuePtr sum = this->_b;
    for (size_t i = 0; i < this->_w.size() && i < x.size(); i++)
    {
        sum = sum + this->_w[i] * x[i];
    }
    return valueTanh(sum);
}

std::vector<ValuePtr> Neuron::parameters()
{
    std::vector<ValuePtr> param;
    for (auto weight : this->_w)
    {
        param.push_back(weight);
    }
    param.push_back(this->_b);
    return param;
}