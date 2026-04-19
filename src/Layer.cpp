#include "Layer.hpp"

Layer::Layer(int nin, int nout)
{
    for (int i = 0; i < nout; i++)
    {
        this->_neurons.push_back(Neuron(nin));
    };
}

std::vector<ValuePtr> Layer::operator()(const std::vector<ValuePtr> &x)
{
    std::vector<ValuePtr> outs;
    for (auto &neuron : this->_neurons)
    {
        outs.push_back(neuron(x));
    }
    return outs;
}

std::vector<ValuePtr> Layer::parameters()
{
    std::vector<ValuePtr> params;

    for (auto &neuron : this->_neurons)
    {
        std::vector<ValuePtr> n_params = neuron.parameters();

        params.insert(params.end(), n_params.begin(), n_params.end());
    }
    return params;
}