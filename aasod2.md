**Laboratory Work No. 2. Lists.**

**Evaluation of Laboratory Works**

Laboratory works are evaluated on a binary scale — pass / fail. To be admitted to the pass, all laboratory works must be completed. The list of minimum requirements for the work is presented below.

**Minimum Requirements**

1. The code must compile without warnings at the maximum warning level. For the GCC compiler, this is the set of flags: `-Wall -Wconversion -Wextra -Wpedantic`. For the MSVC (Visual Studio) compiler, this is the `/W4` flag. For other compilers, agree on compilation settings with the instructor.

2. Global variables must not be used (constants are allowed).

3. Only full English must be used in the code (transliteration is prohibited). Russian is allowed only in comments.

4. Commenting every line of code is prohibited. One brief comment per code block is allowed. Commenting a single line of code is allowed only if it **really** does something unexpected and tricky (but remember, tricky code is bad code!).

5. All code must satisfy a single programming style. You may choose the style to your taste (see, for example, [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html), [GNU C Style](https://www.gnu.org/prep/standards/html_node/Writing-C.html), and others). That is, it is prohibited, for example, to name one function in [CamelCase](https://ru.wikipedia.org/w/index.php?title=CamelCase&stable=1) style and another in [snake_case](https://ru.wikipedia.org/w/index.php?title=Snake_case&stable=1) style. An exception is allowed only for the name of the `main` function. These requirements apply to any named entities in the program — functions, methods, classes, local variables, function and method parameters, file names, and so on.

6. The student provides a link to a git repository. It may be local (on a computer in the classroom or on the student's laptop). The repository must not contain a single commit with the entire lab; it must show the history of work on the laboratory in the form of a series of commits with meaningful titles. The repository must have a correctly configured `.gitignore` file (i.e., the repository must contain only source code files and project files; there must be no intermediate or final compilation results in it).

The laboratory work consists of 2 parts:

- writing a class according to the variant;
- solving one of the practical tasks using the written class.

*You solve a basic or advanced level task of your choice.*

Variants and tasks are distributed according to the table in this file.

**General Requirements**

1. In this work, you must not use any STL containers.

2. The class must be copyable and directly manage the allocated resource.

3. In case of incorrect arguments, exceptions must be thrown via `stdexcept`. Incorrect situations include, for example, accessing a non-existent index, calling an addition operation for two lists of different sizes, and the like.

4. All input/output must be carried out exclusively through `std::cin` and `std::cout`, without using (explicit or implicit) C-style `stdin` and `stdout` streams.

5. The solutions to the tasks must be located outside the class.

**General Part.**

Implement a template class of a linked list **LinkedList** according to your **variant** of the assignment.

Implement an auxiliary structure for representing list elements: **Node.**

The class must implement the following methods:

* Default constructor.
* Copy constructor.
* Constructor that fills the list with random values according to the assignment.

*Note: when generating random arrays, set the seed.*

* Destructor.
* Assignment operation.
* Adding an element to the end of the list — *push_tail*,
* Adding another **LinkedList** list to the end of the list — *push_tail (overloaded method).*
* Adding an element to the beginning of the list — *push_head.*
* Adding a **LinkedList** list to the beginning of the list — *push_head (overloaded method).*
* Removing an element from the beginning of the list — *pop_heads.*
* Removing an element from the end of the list — *pop_tails.*
* Removing all **Node** elements with an information field equal to the passed value — *delete_node.*
* Index access operation (in two variants for reading/writing). In the case of a circular list variant, take the element modulo (i.e., for any index there is a corresponding list element).
* List printing operation (overloaded).

**List Types:**

1) Singly linked linear linked list

2) Doubly linked linear linked list

3) Singly linked circular linked list

4) Doubly linked circular linked list

Perform one of the following tasks according to the variant.

**Tasks:**

***Basic Level***

1. Check whether the list contains cycles. Implement output in such a way that even if the list is cyclic, it is printed correctly.
2. Reverse the list in the opposite direction.
3. Delete the i-th element from the end of the list.
4. Implement the function *print_reverse()* to print the list in reverse order.
5. Find prime numbers in the range [1;N] for an ordered list using the Sieve of Eratosthenes. Implement list output in such a way that only prime numbers are printed.
6. Find [lucky numbers](https://en.wikipedia.org/wiki/Lucky_number) in the range [1;N] for an ordered list. Implement list output in such a way that only unlucky numbers are printed. **The definition of lucky numbers is given at the link above.**
7. Implement a music playlist that works in two modes — normal and shuffle playback. The current track must be printed to the console. Control must be performed using the keyboard.
8. Create two lists of ordered numbers. Merge these two lists so that the sorted order is preserved (the resulting list must not contain duplicates).
9. Implement an address book of a house as an array containing lists as elements. Each array element represents an apartment, and the list elements are the residents of the apartment. By randomly choosing indices, fill the address book with n elements. Implement printing of the house address book.

***Advanced Level***

1. Implement a representation of a polynomial as a list. Only non-zero coefficients must be stored. When adding numbers opposite in sign, a zero parameter must not appear. Find the value of the polynomial at a given value of x.
   *When adding (8x^3+5x+5 and 9x^3 - 5x - 2, the result should be 17x^3 + 3).*
2. Add and multiply two numbers represented as lists. Numbers do not contain leading zeros, except for the number 0 itself. Test the answer on numbers exceeding the maximum value of int. Implement the print operator so that it demonstrates the correctness of the performed operations.
3. Solve the [Tower of Hanoi problem](https://en.wikipedia.org/wiki/Tower_of_Hanoi) using three (or two) lists. Implement list output in the form of towers.
4. Implement a representation of an input path to a non-existent file as a list (Root directory → Folder 1 → … → Folder N → File name). Modify the list so that it points to an existing file in the system, for example, a text file. Restore the path to the file from the list, verify correctness by opening the file. Implement list output in the form of a path to the file.
5. Implement a function that takes a list as input and computes the next state of an elementary cellular automaton [[1](https://en.wikipedia.org/wiki/Elementary_cellular_automaton),[2](https://habr.com/ru/articles/273393/),[see examples](http://atlas.wolfram.com/01/01/)] operating according to the Wolfram code rule. Implement the print operator in the form of the current state of the cellular automaton. (If desired, you can implement a function to save the result in .pbm, .pgm, or .ppm format [[3](https://en.wikipedia.org/wiki/Netpbm_format)]).

**Distribution of Variants**

**THE VARIANT CORRESPONDS TO YOUR NUMBER IN THE INSTRUCTOR'S GRADE SHEET IN THE GOOGLE TABLE (NOT IN YOUR LOCAL ONE)**

| No. in list | List type | Task No. |
| :---: | :---: | :---: |
| **1** | **3** | **(8;3)** |
| **2** | **3** | **(4;1)** |
| **3** | **1** | **(4;3)** |
| **4** | **2** | **(9;2)** |
| **5** | **1** | **(6;2)** |
| **6** | **3** | **(5;1)** |
| **7** | **2** | **(7;4)** |
| **8** | **4** | **(2;1)** |
| **9** | **2** | **(9;2)** |
| **10** | **4** | **(2;5)** |
| **11** | **1** | **(3;4)** |
| **12** | **2** | **(1;2)** |
| **13** | **1** | **(1;4)** |
| **14** | **4** | **(6;2)** |
| **15** | **1** | **(6;3)** |
| **16** | **3** | **(3;2)** |
| **17** | **2** | **(2;1)** |
| **18** | **4** | **(2;5)** |
| **19** | **3** | **(6;1)** |
| **20** | **2** | **(6;2)** |
| **21** | **4** | **(2;1)** |
| **22** | **4** | **(8;5)** |
| **23** | **1** | **(2;3)** |
| **24** | **3** | **(8;1)** |
| **25** | **1** | **(4;2)** |
| **26** | **2** | **(9;4)** |
| **27** | **4** | **(1;2)** |
| **28** | **3** | **(4;1)** |
| **29** | **1** | **(9;4)** |

In parentheses, the first place indicates the basic level, the second — the advanced level.
