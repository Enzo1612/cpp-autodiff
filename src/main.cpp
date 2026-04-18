#include "value.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    ValuePtr a = std::make_shared<Value>(2.0);
    ValuePtr b = std::make_shared<Value>(-3.0);

    ValuePtr c = a + b;
    ValuePtr d = c * a;

    d->backward();

    std::cout << "Data of d: " << d->_data << "\n";
    std::cout << "Gradient of a: " << a->_grad << "\n";

    return 0;
}