#ifndef LAYER_HPP
#define LAYER_HPP

#include "Neuron.hpp"

class Layer
{
public:
    Layer(int nin, int nout);
    std::vector<ValuePtr> operator()(const std::vector<ValuePtr> &x);

    std::vector<ValuePtr> parameters();
    std::vector<Neuron> _neurons;
};

#endif
