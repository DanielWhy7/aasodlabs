# Laboratory Work №2 — Linked Lists

**Variant 1**

| Parameter      | Value                                                        |
|----------------|--------------------------------------------------------------|
| List type      | **3** — Singly linked circular list                          |
| Basic task     | **8** — Merge two sorted lists preserving order, no duplicates |
| Advanced task  | **3** — Tower of Hanoi using three (or two) lists            |

---

## Overview

The project implements a template class `LinkedList<T>` based on a singly linked
**circular** list, together with the helper structure `Node<T>`. The class owns
the dynamically allocated nodes (rule of three), is fully copyable and throws
`std::exceptions` derived from `std::stdexcept` on invalid arguments.

Two practical problems are solved on top of the class:

* **(basic)** merging two sorted lists into a single sorted list without
  duplicates;
* **(advanced)** the Tower of Hanoi, where each rod is represented by a list and
  the state of the rods is printed as towers.

## Repository layout

    .
    ├── include/
    │   ├── linked_list.hpp      # LinkedList<T> and Node<T>
    │   └── tasks.hpp            # declarations of the two task functions
    ├── src/
    │   ├── main.cpp             # demo driver: builds lists, runs both tasks
    │   └── tasks.cpp            # merge_sorted_unique, hanoi
    ├── tests/                   # optional manual checks
    ├── LICENSE/                 # gpl3 License
    ├── .gitignore
    └── README.md

## Requirements

The work follows the minimal requirements of the assignment:

1. Compiles without warnings at the highest warning level:
   * GCC: `-Wall -Wconversion -Wextra -Wpedantic`
   * MSVC: `/W4`
2. No global variables (constants are allowed).
3. All identifiers are written in English; no transliteration. Russian is used
   only inside comments.
4. No line-by-line commenting — at most one short comment per logical block.
5. A single consistent naming style is used for **all** named entities
   (functions, methods, classes, variables, parameters, files).
6. The git repository contains a meaningful series of commits with descriptive
   messages and a properly configured `.gitignore`; build artifacts are never
   committed.

Additional constraints from the assignment:

* No STL containers are used anywhere (`std::vector`, `std::list`, etc. are
  forbidden).
* The class is copyable and directly manages the resource it allocates.
* Invalid situations (index out of range, operations on incompatible lists,
  `pop` on an empty list, etc.) throw exceptions from `<stdexcept>`.
* All I/O goes exclusively through `std::cin` / `std::cout`.
* The task solutions live **outside** the class.

## Building

    g++ -std=c++17 -Wall -Wconversion -Wextra -Wpedantic \
        -Iinclude src/main.cpp src/tasks.cpp -o lab2

Run:

    ./lab2

## `LinkedList<T>` API

The class provides the following members (names may be adjusted to the chosen
style, but must stay consistent across the whole project):

| Member                              | Description                                                        |
|-------------------------------------|--------------------------------------------------------------------|
| `LinkedList()`                      | Default constructor — empty list.                                  |
| `LinkedList(const LinkedList&)`     | Deep copy constructor.                                             |
| `LinkedList(std::size_t, seed)`     | Fills the list with random values (seed is configurable).          |
| `~LinkedList()`                     | Releases all nodes.                                                |
| `operator=`                         | Copy assignment (copy-and-swap).                                   |
| `push_tail(const T&)`               | Appends one element to the tail.                                   |
| `push_tail(const LinkedList&)`      | Appends another list to the tail.                                  |
| `push_head(const T&)`               | Prepends one element.                                              |
| `push_head(const LinkedList&)`      | Prepends another list.                                             |
| `pop_head()`                        | Removes the head element.                                          |
| `pop_tail()`                        | Removes the tail element.                                          |
| `delete_node(const T&)`             | Removes every node whose value equals the argument.                |
| `operator[](std::size_t)`           | Element access for reading; index is taken **modulo size** (circular list). |
| `operator[](std::size_t) const`     | Same, read-only.                                                   |
| `operator<<`                        | Prints the list to `std::cout`.                                    |

Because the list is circular, the index is always reduced modulo the current
size, so any index yields a valid element; an empty list still throws.

## Basic task 8 — merging sorted lists without duplicates

    LinkedList<int> merge_sorted_unique(const LinkedList<int>& first,
                                        const LinkedList<int>& second);

Both inputs are assumed to be sorted in ascending order. The function performs a
linear two-pointer merge, skipping equal neighbours, and returns a new sorted
list that contains every distinct value from either input exactly once.
Duplicate values inside a single input are also collapsed.

Complexity: `O(n + m)` time, `O(n + m)` extra nodes.

## Advanced task 3 — Tower of Hanoi with lists

    void hanoi(std::size_t disk_count);

Three `LinkedList<unsigned>` instances represent the rods `A`, `B`, `C`. The
disks are stored as their sizes (larger value = larger disk), so every rod is a
list sorted in descending order — the smallest disk is always its head. The
recursive solution moves `n` disks from `A` to `C` using `B` as the spare rod,
and after every move the current state of all three rods is printed as ASCII
towers, e.g. for `n = 3`:

    A            B            C
    ============================
    [3]          [ ]          [ ]
    [2]          [ ]          [ ]
    [1]          [ ]          [ ]

Printing is done through the overloaded `operator<<` of the list, so the towers
are rendered by the same code that prints any other list.

## Sample session

    Enter the first sorted list: 1 3 5 7
    Enter the second sorted list: 2 3 4 5 8
    Merged list: [1, 2, 3, 4, 5, 7, 8]

    Enter the number of disks: 2

    Move 1:  A -> B
    A            B            C
    ============================
    [2]          [ ]          [ ]
    [ ]          [1]          [ ]
    ...

## Coding style

* Classes: `CamelCase` (`LinkedList`, `Node`).
* Methods and free functions: `camelCase` (`pushTail`, `popHead`,
  `mergeSortedUnique`).
* Variables and parameters: `camelCase`.
* Constants: `kCamelCase`.
* File names: `snake_case` (`linked_list.hpp`, `tasks.cpp`).
* 4 spaces indentation, braces on the same line, `nullptr` instead of `NULL`.

The exact style is not mandated by the assignment as long as it is applied
uniformly to every named entity in the project.

## Git

The repository contains a step-by-step history of the work, for example:

    init: project skeleton and gitignore
    feat: Node<T> and basic LinkedList<T> skeleton
    feat: copy constructor, assignment, destructor
    feat: push/pop operations for the circular list
    feat: modulo-based operator[] and operator<<
    feat: basic task 8 — merge two sorted lists
    feat: advanced task 3 — Tower of Hanoi with lists
    docs: README
