cmake -G Ninja -B build -Wno-dev

cmake --build build

## Lab Work 1: N-Dimensional Template Vector Class
This repository contains an implementation of a template class for arbitrary-dimension vectors in C++. The implementation fulfills all structural requirements and supports multiple element types, operator overloading, and geometric applications.
------------------------------
## 🛠 Project Structure & Requirements
The codebase is written in strict compliance with the following quality guidelines:

* Compilation Flags: Clean build without warnings under -Wall -Wconversion -Wextra -Wpedantic (GCC/Clang) or /W4 (MSVC).
* Code Style: Unified formatting across all source files (e.g., Google C++ Style Guide / GNU C Style).
* Language: Full English for all naming conventions. Russian is permitted exclusively in short, context-specific comments.
* No Global Variables: Only constant static expressions are used.
* No STL Containers: Developed from scratch directly managing its own dynamic memory, avoiding forbidden containers (only std::string and std::complex are used).

------------------------------
## 🚀 Features## Supported Data Types
The Vector<T> template class is fully specialized and verified at compile-time for:

* int • float • double
* std::complex<float> • std::complex<double> (with custom dot product specialization)

## Core Operations

* Constructors: Size initialization with a default fill value, as well as randomized generation within specified bounds [lower, upper] using <random>.
* Element Access: Overloaded bounds-checked and direct [] operators.
* Arithmetic: Fully supported vector addition (+), subtraction (-), scalar multiplication (omitting position, commutative v * s and s * v), and scalar division (/).
* Dot Product: operator* performing cross-type or inner-type scalar multiplication between two vectors.
* Comparisons: Precision-safe == and != evaluation using a static epsilon constant tolerance field.
* Error Handling: Safe memory bounds management and exception throwing via <stdexcept> for dimension mismatches and out-of-bounds access.

------------------------------
## 📐 Solved Geometric Tasks
The calculations are placed outside the main class architecture as non-member functions:

   1. Triangle Area (Vectors a, b): Calculates the area of a triangle formed by two radius-vectors.
   2. Triangle Bisector: Discovers the radius-vector of the triangle's bisector given boundary vectors a and b.
   3. Parallelogram Angles: Evaluates inner angles for a parallelogram spanned by two radius-vectors.
   4. Perpendicular Vector: Yields an arbitrary normalized unit vector perpendicular to a given input vector.
   5. Triangle Area (Vertices O, A, B): Computes the area of △ OAB using radius-vectors $\vec{a} = \vec{OA}$ and $\vec{b} = \vec{OB}$.

------------------------------
## ⚙️ Compilation & Build
To compile the project with maximum warning checks, use the following command:

g++ -Wall -Wconversion -Wextra -Wpedantic -std=c++17 main.cpp -o vector_app

Running the executable will demonstrate automated validation of all methods, operators, and exceptions using a pseudo-randomized execution setup inside main().
