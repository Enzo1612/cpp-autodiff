#include "../include/autodiff/value.hpp"

int main()
{
    Value *a = new Value(2.0);
    Value *b = new Value(-3.0);

    Value *c = *a + *b;

    c->print();

    std::cout << "Children of c: " << c->_prev.size() << std::endl;
};