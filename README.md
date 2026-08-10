# Student Data Manager
A lightweight C-based CLI application for managing and persisting student records using binary file I/O

### Concepts used to make this project
* **Primitive Data Types & Utility Functions**
  * **Primitive Types**: Standard usage of `int`, `float`, `char` arrays (strings), and `bool` (via `<stdbool.h>`).
  * **Standard Utility Functions**: Case conversion via `tolower()` from `<ctype.h>`.

* **Logic & Control Flow**
  * **Interactive Menu Loop**: Using a `while` loop driven by a boolean flag to keep the CLI running until the user exits.
  * **Branching Control**:
    * `if-else if-else` chains for menu routing and string field comparisons.
    * `switch` statements for mapping status options to human-readable strings.
  * **Linear Search**: Iterating through an array using `strcmp()` to locate matching records by student ID.
  * **Basic CRUD Pattern**: Implementing **C**reate (Append), **R**ead (Scan/View), **U**pdate (Rewrite file with modified array), and **D**elete (Rewrite file skipping target record).

* **User Input & Safety**
  * **Input Validation**: Checking return values of `scanf()` to prevent infinite loops on invalid input types.
  * **Buffer Overflow Prevention**: Specifying explicit field width limits in `scanf` specifiers (e.g., `%14s`, `%19s`).

* **Custom Data Structures**
  * **Enumerations (`enum`)**: Defining named integer constants (`ENROLLED`, `GRADUATED`, `DROPPED_OUT`) for clear status tracking.
  * **Custom Structures (`struct`)**: Grouping mixed data types (`studentID`, `studentName`, `GPA`, `status`) into a single record entity.
  * **Type Aliasing (`typedef`)**: Creating clean type aliases (`student`, `studentStatus`) to avoid repeating `struct` or `enum` keywords.

* **File Operations & I/O**
  * **File Streams (`FILE*`)**: Managing standard file handles using `fopen()` and `fclose()`.
  * **File Access Modes**: Opening files in append mode (`"a"`), read mode (`"r"`), and write mode (`"w"`).
  * **Formatted CSV Operations**:
    * Writing structured CSV records using `fprintf()`.
    * Parsing CSV lines using `fscanf()` with scan-set format specifiers (`%14[^,]`) to parse delimiter-separated fields.

* **Dynamic Memory Management**
  * **Dynamic Heap Allocation (`malloc`)**: Allocating heap memory at runtime based on user-requested capacity.
  * **Dynamic Array Resizing (`realloc`)**: Dynamically doubling array capacity in memory when reading unknown file sizes.
  * **Memory Cleanup (`free`)**: Releasing allocated heap memory before reallocating or exiting to prevent memory leaks.
  * **Pointer Type Casting**: Explicit pointer casting `(int *)` when reading or writing directly to `enum` types via address references.
 
 Although the list provided above is AI generated (I'm too lazy to manually list everything), the code is **mostly** written by me, used some AI along with external resources to learn totally new concepts.
