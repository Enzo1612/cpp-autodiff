#ifndef NEURON_HPP
#define NEURON_HPP

#include "value.hpp"
#include <vector>
#include <random>

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

class Neuron
{
public:
    Neuron(int nin);

    ValuePtr operator()(const std::vector<ValuePtr> &x);

    std::vector<ValuePtr> parameters();
    std::vector<ValuePtr> _w;
    ValuePtr _b;
};

#endif