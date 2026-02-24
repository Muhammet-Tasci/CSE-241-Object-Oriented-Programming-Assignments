# Assignment 4: Polymorphic Connect Four Engine

## Overview
This project serves as the capstone assignment for the CSE 241 Object Oriented Programming course. It re-engineers the previous Connect Four game into a robust, extensible **Object-Oriented Framework**. By leveraging **Inheritance** and **Polymorphism**, the system supports multiple game variants (Plus, Diagonal, and Undo modes) derived from a single abstract interface. The project adheres to strict memory constraints, utilizing raw pointers and dynamic allocation instead of standard containers.

## System Architecture & Class Hierarchy
The core of the project is built upon a flexible inheritance tree designed for code reuse and extensibility:

1.  **`ConnectFourAbstract` (Abstract Base Class):**
    * Defines the blueprint for the game engine.
    * Manages the dynamic 2D board (`Cell**`) and file I/O operations.
    * Enforces implementation of critical logic via pure virtual functions (e.g., `isGameOver()`).
2.  **`ConnectFourPlus` (Derived Class):**
    * Implements a game mode where winning is only possible via **Horizontal** or **Vertical** connections.
3.  **`ConnectFourDiag` (Derived Class):**
    * Implements a game mode where winning is restricted to **Diagonal** connections only.
4.  **`ConnectFourPlusUndo` (Derived from `ConnectFourPlus`):**
    * Extends the 'Plus' ruleset by adding a history tracking mechanism.
    * Allows the user to **Undo** moves, reverting the game state (board and turn) to previous steps using a dynamically managed move stack.

## Key Features
* **Runtime Polymorphism:** The `main` driver utilizes base class pointers (`ConnectFourAbstract*`) to instantiate and control different game modes dynamically based on user input.
* **Irregular Board Support:** Capable of loading and playing on non-rectangular, distinctively shaped boards defined in text files (e.g., `denemetahtasi-1.txt`).
* **"Undo" Mechanics:** Implements a custom stack-based history system (without `std::vector`) to store column indices, enabling the reversal of gameplay actions.
* **Smart AI Opponent:** Contains a defensive AI that adapts to the current board state, blocking player wins while pursuing its own connections.
* **Robust File Parsing:** dynamic file reading logic that interprets board shapes (`*`, ` `) and current game states (`X`, `O`) from saved files.

## Technical Implementation
This assignment demonstrates advanced C++ proficiency:
* **Abstract Classes & Pure Virtual Functions:** Enforces a strict contract for derived classes, ensuring every game mode implements its own win conditions.
* **Virtual Destructors:** Ensures proper memory cleanup for derived objects when deleted through a base class pointer, preventing memory leaks.
* **Namespace Encapsulation:** All classes are wrapped within the `HW4` namespace to prevent naming collisions and maintain modularity.
* **Manual Memory Management:**
    * **Board:** Allocated as `Cell**` (array of pointers).
    * **History:** The Undo feature uses a dynamically resized `int*` array to track moves.
    * **Cleanup:** Meticulous `delete` and `delete[]` calls in destructors.
* **Operator Overloading:** Extensive use of overloaded operators in the `Cell` class (`++`, `==`, `<<`, `>>`) for intuitive state manipulation.

## Execution Modes
The program offers a CLI menu to select the game variant:
* **[P] Plus Mode:** Traditional movement, but wins restricted to orthogonal lines.
* **[D] Diagonal Mode:** Wins restricted to diagonal lines.
* **[U] Undo Mode:** Plus ruleset with the ability to reverse moves by typing `undo`.