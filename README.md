# C++ Reverse-Mode Automatic Differentiation

A lightweight C++ implementation of reverse-mode automatic differentiation using a dynamic computational graph, inspired by Andrej Karpathy's [micrograd](https://github.com/karpathy/micrograd).

The project explores how gradients can be computed through elementary operations without relying on an external automatic differentiation library.

## Features

- Scalar-valued computation graph
- Automatic gradient propagation using reverse-mode differentiation
- Operator overloading for addition, subtraction, multiplication, and division
- Power operation through `valuePow`
- Hyperbolic tangent through `valueTanh`
- Topological traversal of the computation graph during backpropagation
- Shared ownership of graph nodes using `std::shared_ptr`

## Example

Consider the expression

\[
d = (a+b)a
\]

with \(a=2\) and \(b=-3\).

The forward pass computes

\[
d=(2-3)\times 2=-2.
\]

The gradients are

\[
\frac{\partial d}{\partial a}=2a+b=1,
\qquad
\frac{\partial d}{\partial b}=a=2.
\]

Because `a` contributes to the result through two paths in the computational graph, its gradient accumulates contributions from both paths.

The corresponding C++ example:

```cpp
ValuePtr a = std::make_shared<Value>(2.0);
ValuePtr b = std::make_shared<Value>(-3.0);

ValuePtr c = a + b;
ValuePtr d = c * a;

d->backward();
```

Running the current demo prints:

```text
Data of d: -2
Gradient of a: 1
```

## Implementation

The implementation is organized into three source files:

- `src/value.hpp`: scalar value representation and operator declarations
- `src/value.cpp`: elementary operations, local derivatives, and backpropagation
- `src/main.cpp`: demonstration of the computation graph

Each operation creates a new value and records its parents and local backward function. During `backward()`, the graph is traversed in reverse topological order to propagate gradients.

## Build and Run

### Using g++

Requires a C++17-compatible compiler.

```bash
g++ -std=c++17 -I ./src src/value.cpp src/main.cpp -o demo
./demo
```

### Using CMake

```bash
cmake -S . -B build
cmake --build build
./build/demo
```

## Current Scope

This is a small educational implementation focused on scalar operations and reverse-mode differentiation. It does not currently provide tensor operations or a complete neural network training framework.

## Future Improvements

- Add automated tests for forward values and gradients
- Validate gradients against numerical finite differences
- Build higher-level abstractions such as neurons, layers, and multilayer perceptrons
- Explore training a small neural network using the engine
