# Assignment 2: CPU Simulator with Memory & OOP

## Overview
This project is the second assignment for the CSE 241 Object Oriented Programming course. Building upon the foundation of the previous simple CPU simulator, this iteration introduces a dedicated **Virtual Memory** system and transitions the entire codebase to an **Object-Oriented** architecture. The simulator now models a CPU with both registers and addressable memory, capable of executing complex assembly programs that require data storage and retrieval.

## Key Features
* **Object-Oriented Design (OOP):** The entire CPU logic is encapsulated within a `CPU` class, protecting internal states (registers and memory) via `private` access specifiers and exposing functionality through `public` member functions.
* **Virtual Memory System:** Implements a 100-byte unsigned integer memory array. The instruction set supports direct memory addressing using the `#` prefix (e.g., `MOV R1, #50` loads data from memory address 50).
* **Expanded Instruction Set (ISA):**
  * **Memory Operations:** `MOV`, `ADD`, and `SUB` instructions now support memory addresses as both sources and destinations.
  * **Conditional Branching:** Introduced `JPN` (Jump if Negative or Null) to enable more complex control flow logic based on register values (Jump if Value $\le$ 0).
* **Enhanced Debugging (Option 2):** Added a new execution mode (`option 2`) that visualizes the entire state of the memory map after each instruction, alongside the register dumps.

## Technical Implementation
This assignment demonstrates the practical application of core OOP concepts and advanced C++ features:
* **Encapsulation:** Registers (`R1-R6`) and `memory[100]` are strictly managed within the class, preventing unauthorized external modification.
* **Custom String Parsing:** Complies with strict constraints by avoiding C-style string functions (`strtok`, `atoi`). Instead, it utilizes `std::string` methods (`find`, `substr`) to parse complex instruction formats like `ADD R1, #10`.
* **Method Overloading:** Although not strictly enforced by the compiler for distinct instruction names, the internal logic efficiently handles polymorphic behavior for instructions that accept different operand types (Register vs. Constant vs. Memory Address).
* **Address Decoding:** Implements a robust decoding logic to differentiate between immediate values (constants) and memory references (prefixed with `#`) during runtime.

## Usage
The program takes command-line arguments to control the simulation mode:
* **Mode 0:** Runs the program silently and prints the final output.
* **Mode 1:** Prints each instruction and the state of the **Registers** step-by-step.
* **Mode 2:** Prints each instruction, the state of the **Registers**, and the full **Memory Map** step-by-step.