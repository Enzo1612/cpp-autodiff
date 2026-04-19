#ifndef MLP_HPP
#define MLP_HPP

#include "Layer.hpp"

class MLP
{
public:
    MLP(int nin, const std::vector<int> &nouts);

    std::vector<ValuePtr> operator()(std::vector<ValuePtr> x);

    std::vector<ValuePtr> parameters();

    std::vector<Layer> _layers;
};

#endif