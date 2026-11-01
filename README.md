# cpp-playground

Algorithm problems and system designs, worked through in modern C++ (C++17).

Each problem lives in its own folder with:

- a short explanation: the problem, the approach, why it works, and its time/space complexity
- the C++ solution
- GoogleTest tests, including edge cases
- a diagram where one helps (Mermaid / PlantUML sources)

## Problems

| # | Problem | Pattern | Time / Space |
|---|---|---|---|
| 387 | [First Unique Character in a String](problems/0387-first-unique-character) | Hashing / counting | O(n) / O(1) |

## Building and testing

Needs CMake ≥ 3.20, a C++17 compiler and GoogleTest.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
