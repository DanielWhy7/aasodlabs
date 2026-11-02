## Languages
English [Russian](README-RU.md) [German](README-DE.md) [Japanese](README-JA.md)

# Laboratory Work №2 — Linked Lists (Variant 1, C++26)

| Parameter      | Value                                                          |
|----------------|----------------------------------------------------------------|
| List type      | **3** — Singly linked circular list                            |
| Basic task     | **8** — Merge two sorted lists preserving order, no duplicates |
| Advanced task  | **3** — Tower of Hanoi using three (or two) lists              |
| Language       | **C++26** (modules, contracts, `import std;`)                  |
| Build system   | **CMake 4.1+** with Ninja, presets for GCC / Clang / MSVC      |

---

## Overview

The project implements a template class `linked_list<T>` based on a singly
linked **circular** list, together with the helper structure `node<T>`. The
class owns the dynamically allocated nodes (rule of three), is fully copyable
and throws `std::stdexcept` exceptions on invalid arguments.

Two practical problems are solved on top of the class:

* **(basic)** merging two sorted lists into a single sorted list without
  duplicates;
* **(advanced)** the Tower of Hanoi, where each rod is represented by a list
  and the state of the rods is printed as ASCII towers.

The code is written in **K&R style** (`type name() {`, 2-space indent,
`snake_case` identifiers) and uses **C++26 features** as documented on
cppreference:

* **Named modules** — `import std;` brings the entire standard library into
  scope without headers;
* **Contracts** — `contract_assert` (and the `pre` / `post` declarator forms)
  express internal invariants such as `tail_->next == head_` and
  `size_ == expected`. User-facing errors still use exceptions so that the
  caller can recover.

## Repository layout

```
.
├── CMakeLists.txt
├── CMakePresets.json
├── .gitignore
├── README.md
├── LICENSE                       # GPLv3
└── src/
    ├── linked_list.cppm          # linked_list<T> and node<T>      (module interface)
    ├── tasks.cppm                # tasks module                   (module interface)
    ├── tasks.cpp                 # tasks module                   (implementation)
    ├── main.cpp                  # ▶ interactive program   — has main()
    └── test.cpp                  # ▶ automated test suite  — has main()
```

Both `main.cpp` and `test.cpp` define their own `main()`; they are compiled
into **two separate executables** (`main` and `tests`) that share a static
library `lablib` holding the two modules.

## Requirements

The work follows the minimal requirements of the assignment:

1. Compiles without warnings at the highest warning level:
   * GCC / Clang: `-Wall -Wconversion -Wextra -Wpedantic`
   * MSVC: `/W4 /utf-8`
2. No global variables (constants are allowed).
3. All identifiers are written in English; no transliteration. Russian is used
   only inside comments.
4. No line-by-line commenting — at most one short comment per logical block.
5. A single consistent naming style (K&R / `snake_case`) is applied to **all**
   named entities — functions, methods, classes, variables, parameters, files.
6. The git repository contains a meaningful series of commits with descriptive
   messages and a properly configured `.gitignore`; build artifacts are never
   committed.

Additional constraints from the assignment:

* **No STL containers** are used anywhere (`std::vector`, `std::list`, etc. are
  forbidden).
* The class is copyable and directly manages the resource it allocates.
* Invalid situations (`operator[]` on empty list, `pop_head` / `pop_tail` on
  empty list, …) throw exceptions from `<stdexcept>`.
* All I/O goes exclusively through `std::cin` / `std::cout`.
* The task solutions live **outside** the class — they are free functions in
  the `tasks` module.

## Building

### Using CMake presets (recommended)

```sh
cmake -G Ninja -B build -Wno-dev
cmake --build build
```

The build produces two executables under `/build`:

| Binary | Purpose |
|--------|---------|
| `main` | interactive program — runs task 8 then task 3 |
| `tests` | automated test suite (17 tests); exits `0` on success |

### Using the compiler directly (GCC 16.1+)

```sh
g++ -std=c++26 -fmodules -fcontracts \
    -Wall -Wconversion -Wextra -Wpedantic \
    --compile-std-module \
    src/main.cpp src/tasks.cpp -o main
g++ -std=c++26 -fmodules -fcontracts \
    -Wall -Wconversion -Wextra -Wpedantic \
    --compile-std-module \
    src/test.cpp src/tasks.cpp -o tests
```

`-fcontracts` enables the C++26 contract assertions used in `linked_list` and
in `tasks.cpp`.

## Running

```sh
# 1) Automated test suite first
./build/linux-debug/tests
# 2) Then the interactive program
./build/linux-debug/main
```

### Test suite output

```
=== Automated tests ===
  PASS: default constructor
  PASS: random fill constructor
  PASS: push_tail / push_head
  PASS: modulo indexing
  PASS: empty index throws
  PASS: copy constructor
  PASS: assignment
  PASS: pop_head
  PASS: pop_tail
  PASS: delete_node
  PASS: push_tail(list)
  PASS: push_head(list)
  PASS: merge_sorted_unique
  PASS: merge with empty
  PASS: merge both empty
  PASS: merge collapses duplicates
  PASS: hanoi(0) is a no-op
=== All tests passed ===
```

### Interactive session

```
Task 8: merging two sorted lists without duplicates
Enter first list (count then values): 4 1 3 5 7
Enter second list (count then values): 5 2 3 4 5 8
Merged: [1, 2, 3, 4, 5, 7, 8]

Task 3: Tower of Hanoi
Enter number of disks: 3

Initial state:
A            B            C
============================
[1]          [ ]          [ ]
[2]          [ ]          [ ]
[3]          [ ]          [ ]

Move 1: A -> C
...
Total moves: 7
```

## `linked_list<T>` API

| Member                                          | Description                                                          |
|-------------------------------------------------|----------------------------------------------------------------------|
| `linked_list()`                                 | Default constructor — empty list.                                    |
| `linked_list(const linked_list&)`               | Deep copy constructor.                                               |
| `linked_list(std::size_t, seed, min, max)`      | Random-fill constructor (`requires std::integral<T>`).               |
| `~linked_list()`                                | Releases all nodes.                                                  |
| `operator=`                                     | Copy assignment (copy-and-swap).                                     |
| `swap(linked_list&)`                            | O(1) member swap.                                                    |
| `size()` / `empty()`                            | Size queries.                                                        |
| `push_tail(const T&)`                           | Appends one element to the tail.                                     |
| `push_tail(const linked_list&)`                 | Appends another list to the tail.                                    |
| `push_head(const T&)`                           | Prepends one element.                                                |
| `push_head(const linked_list&)`                 | Prepends another list.                                               |
| `pop_head()`                                    | Removes the head element; throws on empty.                           |
| `pop_tail()`                                    | Removes the tail element; throws on empty.                           |
| `delete_node(const T&)`                         | Removes every node whose value equals the argument.                  |
| `operator[](std::size_t)`                       | Element access; index is reduced **modulo size** (circular list).    |
| `operator[](std::size_t) const`                 | Same, read-only.                                                     |
| `operator<<`                                    | Prints the list to `std::ostream` (used by `std::cout`).             |

Because the list is circular, any index is reduced modulo the current size, so
every index yields a valid element. An empty list still throws
`std::out_of_range`.

## Basic task 8 — merging sorted lists without duplicates

```cpp
linked_list<int> merge_sorted_unique(const linked_list<int>& first,
                                     const linked_list<int>& second);
```

Both inputs are assumed to be sorted in ascending order. The function performs
a linear **two-pointer merge**, skipping equal neighbours, and returns a new
sorted list that contains every distinct value from either input exactly once.
Duplicates *within* a single input are also collapsed.

Complexity: `O(n + m)` time, `O(n + m)` extra nodes.

## Advanced task 3 — Tower of Hanoi with lists

```cpp
void hanoi(unsigned int disk_count);
```

Three `linked_list<unsigned>` instances represent the rods `A`, `B`, `C`. Disks
are stored as their sizes (larger value = larger disk), so every rod is a list
sorted in descending order — the smallest disk is always its **head**. This
makes the legal move `pop_head` on the source rod + `push_head` on the destination rod, because in Hanoi only the top (smallest) disk can move.
The recursive solution moves `n` disks from `A` to `C` using `B` as the spare
rod. After every move the state of all three rods is printed as ASCII towers
(e.g. `[3]` for a disk of size 3, `[ ]` for an empty slot). Because the rods
are drawn bottom-aligned, disks always "rest" on the base.

The recursive solution runs in `2^n - 1` moves.

## C++26 features used

| Feature | Where | Purpose |
|---------|-------|---------|
| **Named modules** (`import std;`) | `linked_list.cppm`, `tasks.cppm`, `tasks.cpp`, `main.cpp`, `test.cpp` | Faster, cleaner compilation without preprocessor headers. |
| **Contracts** (`contract_assert`) | `linked_list` member functions | Assert internal invariants (`tail_->next == head_`, `size_ == other.size_`, …) in debug builds. |
| **`requires` clauses** | `linked_list(count, seed, min, max)` | Restrict the random-fill constructor to integral types. |
| **Standard library modules** | `import std;` | The entire standard library is available without `#include`. |

> **Note:** pattern matching did **not** make it into C++26; it is deferred to
> C++29. The project therefore does not use `std::match`.

## Module layout (why `tasks.cppm` + `tasks.cpp`?)

`tasks` is split into a **module interface unit** (`tasks.cppm`, which declares
the two exported functions) and a **module implementation unit**
(`tasks.cpp`, which defines their bodies). This is the module-era equivalent of
splitting a header and its `.cpp`:

* Editing the body of `hanoi` or `merge_sorted_unique` recompiles only
  `tasks.cpp`, **not** `main.cpp` or `test.cpp`.
* File-local helpers (`print_disk_field`, `print_rod_cell`, `print_state`,
  `hanoi_recursive`) live in `tasks.cpp` as `static` functions and are
  invisible to consumers of the module.

`linked_list` is **not** split the same way because it is a template — its full
definition must be visible to every translation unit that instantiates it, so
everything lives in `linked_list.cppm`.

## Coding style

K&R / Linux-kernel flavour:

* Classes, structs, functions, variables, parameters, files: `snake_case`
  (`linked_list`, `node`, `push_tail`, `merge_sorted_unique`).
* **Return type and function name on the same line**, opening brace on the
  same line:

  ```cpp
  int main() {
    ...
  }
  ```

* 2-space indentation.
* `nullptr` instead of `NULL`, `static_cast<>` instead of C casts.
* No space between a function name and `(`.

The style is applied uniformly to every named entity in the project.
