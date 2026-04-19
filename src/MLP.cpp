#include "MLP.hpp"

MLP::MLP(int nin, const std::vector<int> &nouts)
{
    // Combine nin and nouts into one list
    std::vector<int> sz = {nin};
    sz.insert(sz.end(), nouts.begin(), nouts.end());

    // Build layers connecting sz[i] to sz[i+1]
    for (size_t i = 0; i < nouts.size(); i++)
    {
        this->_layers.push_back(Layer(sz[i], sz[i + 1]));
    }
}

std::vector<ValuePtr> MLP::operator()(std::vector<ValuePtr> x)
{
    for (auto &layer : this->_layers)
    {
        x = layer(x);
    }
    return x;
}

std::vector<ValuePtr> MLP::parameters()
{
    std::vector<ValuePtr> params;

    for (auto &layer : this->_layers)
    {
        std::vector<ValuePtr> l_params = layer.parameters();

        params.insert(params.end(), l_params.begin(), l_params.end());
    }
    return params;
}