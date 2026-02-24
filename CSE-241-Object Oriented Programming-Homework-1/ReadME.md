# Assignment 1: Simple CPU Simulator

## Overview
This project is the first assignment for the CSE 241 Object Oriented Programming course. It involves designing and implementing a simulation of a simplified Central Processing Unit (CPU) using C++. The program acts as an interpreter for a custom assembly-like instruction set, reading commands from a text file and executing them on a virtual set of registers. 

*Note: As per the assignment constraints, this project is implemented using a purely procedural approach (functions only) to demonstrate proficiency in C++ syntax and standard libraries before transitioning to Object-Oriented paradigms.*

## Key Features
* **Instruction Set Architecture (ISA):** Supports a fundamental set of CPU instructions including:
  * **Data Movement:** `MOV` (Register-to-Register and Constant-to-Register).
  * **Arithmetic Operations:** `ADD` and `SUB` for mathematical computations.
  * **Control Flow:** `JMP` for conditional and unconditional branching/loops.
  * **I/O Operations:** `PRN` to print register values and `HLT` to terminate execution.
* **Virtual Memory Model:** Simulates 6 general-purpose integer registers (`R1` through `R6`) to store and manipulate data during execution.
* **Dual Execution Modes:**
  * **Mode 0 (Run):** Executes the entire program silently and prints the final result.
  * **Mode 1 (Debug/Trace):** Executes the program step-by-step, printing the instruction line and the state of all registers after each step for debugging purposes.
* **Robust File Parsing:** dynamic file reading using `std::vector` and `std::string` manipulation to parse opcodes and operands, handling potential syntax errors gracefully.

## Technical Implementation
This project marks the transition from C to C++, utilizing specific C++ features:
* **String Manipulation:** Extensive use of the `std::string` class for parsing instructions, replacing legacy C-string functions.
* **Standard I/O Streams:** Implementation of `std::cin` and `std::cout` via the `iostream` library, strictly avoiding C-style `printf`/`scanf`.
* **Function Overloading:** Demonstrates polymorphism by overloading the `jump()` instruction to handle both direct jumps (unconditional) and register-based jumps (conditional).
* **Reference Parameters:** Utilizes C++ "pass-by-reference" (`int &a`) syntax for efficient register updates within arithmetic functions.

## Algorithm Demonstration
The provided `instructions.txt` file contains a custom assembly program written for this CPU. It implements a loop algorithm to calculate the **sum of squares of integers from 1 to 10**, storing the result in the registers and printing the final output.