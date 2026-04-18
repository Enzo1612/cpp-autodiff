# cpp-autodiff

A lightweight C++ implementation of **reverse-mode automatic differentiation** with a dynamic computational graph (inspired by MicroGrad/PyTorch internals).

## Features

- Scalar `Value` node with:
  - `data`
  - `grad`
  - operation label (`op`)
  - parents (`prev`)
  - local backward function
- Supported ops:
  - `+`, `-`, `*`, `/`, `pow`
- Topological graph traversal for `backward()`

## Project Structure

- `src/value.hpp` — `Value` class + operator declarations
- `src/value.cpp` — operator implementations + `backward()`
- `src/main.cpp` — small demo

## Build (g++)

From project root:

```bash
g++ -std=c++17 -I ./src src/value.cpp src/main.cpp -o demo
./demo
```

## Build (CMake)

```bash
cmake -S . -B build
cmake --build build
./build/demo
```

## Example

```cpp
ValuePtr a = std::make_shared<Value>(2.0);
ValuePtr b = std::make_shared<Value>(-3.0);

ValuePtr c = a + b;
ValuePtr d = c * a;

d->backward();
```

## Next Steps

- Add `Neuron`, `Layer`, `MLP`
- Add activation functions (`tanh`, `relu`)
- Add training loop and simple dataset
- Add tests
