# Vaccine Management System

## Overview
This repository contains a C program developed for the "Introdução aos Algoritmos e Estruturas de Dados" (IAED) course. The project implements a robust command-line application to manage vaccine batches, track patient inoculations, and handle stock based on expiration dates and system time progression.

## Features & Commands
The system operates through a command-line interface, processing various operations to manage the vaccine workflow. The supported commands include:
* **`c` (Create Batch):** Adds a new batch of vaccines to the system, specifying the batch name, expiration date, quantity, and vaccine type.
* **`l` (List Batches):** Lists all available vaccine batches, sorted chronologically by expiration date and alphabetically by name. Can also filter by specific vaccine types.
* **`t` (Time Progression):** Advances the system's current date.
* **`a` (Apply Vaccine):** Administers a vaccine to a patient. The system automatically selects the valid batch with the closest expiration date. It prevents duplicate daily vaccinations for the same patient.
* **`r` (Remove Batch):** Removes a specific batch from the system or depletes its stock.
* **`u` (List Inoculations):** Lists all patient inoculations or filters the vaccination history for a specific patient.
* **`d` (Delete Inoculation):** Removes inoculation records based on the patient's name, specific dates, or specific batch numbers.
* **`q` (Quit):** Safely exits the program and frees all allocated memory.

## Architecture and File Structure
The project is modular and strictly organized into different headers and source files to ensure readability and maintainability:
* **`project.c`**: The main entry point. Initializes the system state, handles command parsing, and safely frees memory upon exit.
* **`principais.c` / `.h`**: Core logical functions that directly implement the system commands.
* **`auxiliares.c` / `.h`**: Helper functions for date validation, sorting algorithms, memory reallocation, and specific data checks.
* **`structs.h`**: Contains the core Data Structures (`Sys`, `Lote`, `Inoculacao`, `Data`).
* **`constants.h`**: Defines system limits and standardizes error messages in both Portuguese and English.

## Dynamic Memory Management
The project makes extensive use of dynamic memory allocation (`malloc`, `realloc`, `free`). The inoculations array automatically expands as new patients are vaccinated, ensuring the system can handle a virtually unlimited number of records without hardcoded limits.

## Compilation and Execution
To compile the project, use a C compiler such as `gcc`:
bash
gcc -Wall -Wextra -O3 *.c -o vaccin

To run the program:
./vaccines

Language Support:
By default, the system outputs error messages in English. You can run the program with the pt argument to switch all error messages to Portuguese:
./vaccines pt

## License

MIT License © 2025 Guilherme Marques.
