# Compilers - Örebro University (Erasmus Exchange)

This repository contains a collection of projects developed for the **Compilers** course during my Erasmus exchange at **Örebro University**, Sweden.

The project covers the complete lifecycle of compiler design—from lexical analysis and manual parsing to automated generators and the implementation of a recursive execution engine for a custom language.

## 👤 Author
* **Rafael Pino Rodríguez** · [LinkedIn](https://www.linkedin.com/in/rafael-pino-rodr%C3%ADguez-472918211)

## 🛠️ Technologies & Tools
* **Languages:** C, C++
* **Generators:** Flex (Lexical Analysis), Bison (Syntactic Analysis)
* **Environment:** Linux / Makefile

---

## 📂 Assignments Overview

### 1. Introduction & Debugging
* Resolved memory leaks and segmentation faults in C++ code.
* Analyzed core compiler phases: scanner, parser, and intermediate code generation.
* Studied C preprocessor limitations regarding recursive macros.

### 2. Predictive Parsing
* Designed grammars for arithmetic expressions and assignments.
* Implemented a manual predictive recursive-descent parser.
* Extended the symbol table to store and evaluate variable values.

### 3. Automated Generators (Bison)
* Migrated manual parsing logic to **Bison** for more efficient grammar management.
* Added support for division (`/`), modulo (`%`), comparisons (`<`, `>`), bitwise operators (`&`, `|`), and the ternary operator (`? :`).
* Transitioned the entire project structure to **C++**.

### 4. DFA & Flex
* Implemented a Deterministic Finite Automaton (DFA) from scratch for sequence recognition.
* Integrated **Flex** to replace the manual scanner, improving tokenization of identifiers and reserved words.

### 5. Abstract Syntax Trees (AST)
* Refactored the parser to build a **Syntax Tree** using node pointers instead of immediate emission.
* Developed `mknode` and `mkleaf` functions for tree construction.
* Implemented a tree printer to visualize code hierarchy.

### 6. Interpreter & Execution Engine
* Resolved the "dangling else" ambiguity by enforcing explicit block structures.
* Developed a recursive **Execution Engine** in `syntaxTree.c` that traverses the AST to execute instructions.
* Full support for `if-else` conditionals, `while` loops, and `read`/`print` statements.

---

## 🚀 How to Run
Each assignment includes its own `Makefile`. To compile and run the final version (Assignment 6):

```bash
cd assignment6/29
make
./infix2postfix
```

---

## Example program

```text
read(i);
while (i > 0) {
    if ((i mod 100) < 1) {} else {
        print(i);
    }
    i = i - 1;
}
done
```
