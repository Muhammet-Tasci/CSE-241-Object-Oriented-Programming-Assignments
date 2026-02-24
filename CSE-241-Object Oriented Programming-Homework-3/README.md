# Assignment 3: Dynamic Connect Four Game

## Overview
This project is the third assignment for the CSE 241 Object Oriented Programming course. It features a fully functional **Connect Four** game engine developed in C++. Unlike standard grid-based games, this implementation supports **irregularly shaped boards** loaded from text files. The project strictly adheres to constraints prohibiting standard containers (like `std::vector`), forcing the manual management of **Dynamic Memory** for all data structures.

## Key Features
* **Dynamic Board Architecture:** Instead of a fixed rectangular grid, the game reads custom board configurations from `.txt` files. This allows for gameplay on varying shapes (e.g., diamond, pyramid) defined by the user.
* **Intelligent Computer Opponent:** Implements a single-step lookahead AI (`playComputer`). The AI intelligently defends against the user by blocking winning moves and seizes opportunities to connect 4 cells vertically, horizontally, or diagonally.
* **Game State Persistence:** Users can save the current state of the game (including board shape and piece positions) to a file and resume later, ensuring continuity.
* **Global Game Statistics:** Utilizes `static` member variables to track shared statistics, such as the total number of "living cells" (active pieces) across all concurrent game instances.

## Technical Implementation
This assignment demonstrates mastery of advanced C++ and OOP concepts:
* **Nested Classes (Inner Classes):** The `Cell` class is encapsulated within the `ConnectFour` class, enforcing strong modularity. Each cell manages its own state (position, symbol) and content logic.
* **Dynamic Memory Management:** Since vectors were prohibited, the game board is constructed using pointers to pointers (`Cell**`). Memory is explicitly allocated (`new`) during initialization and rigorously deallocated (`delete`) in the destructor to prevent memory leaks.
* **Operator Overloading:**
  * `operator<<`: Custom stream insertion for printing individual cells.
  * `operator==` / `operator!=`: Compares two game states or cells for equality.
  * `operator++` (Prefix & Postfix): Cycles the state of a cell (e.g., Empty `*` → User `O` → Computer `X`).
* **File I/O Parsing:** Robust parsing logic to read board dimensions and initial states from external text files, handling variable row lengths and non-playable spaces.

## Usage
The program prompts the user to enter a board filename at startup.
1. **Load Board:** The game initializes based on the shape defined in the text file.
2. **Gameplay:**
   - **User:** Enters a column letter (e.g., 'A', 'B') to drop a piece.
   - **Computer:** Automatically calculates and plays the optimal move.
3. **Save/Exit:** The game detects win conditions or draws. The state can be saved to `saved_board.txt` for future analysis.