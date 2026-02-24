# CSE 241: Object Oriented Programming (C++) 🚀

Welcome to my portfolio of C++ programming assignments completed for the **CSE 241 - Object Oriented Programming** course. 

This repository serves as a comprehensive record of my transition from procedural programming to advanced **Object-Oriented paradigms**. Over the course of 4 intensive assignments, I have designed complex systems (CPU Simulators, Game Engines) from scratch, strictly adhering to low-level memory constraints and rigorous software engineering principles.

## 🧠 Core Concepts & Skills Demonstrated
Throughout these projects, I have developed and applied deep technical knowledge in:
* **Object-Oriented Design:** Encapsulation, Inheritance, Polymorphism, and Abstraction.
* **Memory Management:** Manual dynamic memory allocation (`new`, `delete`), pointer arithmetic, and deep copy logic without relying on `std::vector`.
* **Advanced C++ Features:** Operator Overloading, Virtual Functions, Abstract Base Classes, and Namespaces.
* **System Design:** Building scalable architectures using file I/O, custom parsing logic, and modular class hierarchies.

## 📂 Project Evolution
Each assignment in this repository represents a specific milestone in software architecture:

### 🔹 [Assignment 1: Simple CPU Simulator](./CSE-241-Object%20Oriented%20Programming-Homework-1)
* **Focus:** Procedural Programming & C++ Syntax.
* **Description:** A text-based CPU interpreter that executes Assembly-like instructions (MOV, ADD, JMP). Implemented using only functions and standard I/O streams to grasp the fundamentals of C++.

### 🔹 [Assignment 2: CPU with Virtual Memory](./CSE-241-Object%20Oriented%20Programming-Homework-2)
* **Focus:** Encapsulation & Class Design.
* **Description:** Transformed the CPU simulator into a full **Class** structure. Introduced a **Virtual Memory** system, separating internal state (private registers) from external interfaces (public methods).

### 🔹 [Assignment 3: Dynamic Connect Four](./CSE-241-Object%20Oriented%20Programming-Homework-3)
* **Focus:** Dynamic Memory & Operator Overloading.
* **Description:** A Connect Four game engine supporting **irregular board shapes**. Since `std::vector` was prohibited, I implemented custom dynamic arrays and overloaded operators (`++`, `==`, `<<`) to manage game state and object interactions.

### 🔹 [Assignment 4: Polymorphic Game Engine](./CSE-241-Object%20Oriented%20Programming-Homework-4)
* **Focus:** Inheritance, Polymorphism & Abstract Classes.
* **Description:** The capstone project. A robust game framework where multiple game modes (Plus, Diagonal, Undo) derive from a single `ConnectFourAbstract` base class. It features a custom **Undo** mechanism using a dynamic stack and utilizes **Runtime Polymorphism** to manage game logic.

---

## 🛠️ Technical Constraints
A key feature of these assignments is the **restriction on Standard Template Library (STL)** containers. To demonstrate true mastery of C++ internals:
* **No `std::vector`:** All dynamic lists and history stacks were implemented manually using raw pointers and size tracking.
* **No `std::string` helpers:** Complex parsing logic (e.g., separating instructions from operands) was built using fundamental string manipulation techniques.

*Feel free to explore the individual assignment folders to see the source code, detailed documentation, and the architectural decisions behind each project!*
