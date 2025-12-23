# Library-Management System
Simple library system using file functions and memory management in C
This project is an automation system developed within the scope of my Computer Programming course, using the C programming language to manage books and categories.

The project is designed to effectively demonstrate **structures (structs)**, **pointers**, **dynamic memory management (malloc/realloc/free)**, and **file I/O** techniques.

## 🚀 Features

* **Dynamic Data Structures:** Categories and books are stored in nested dynamic structures. When capacity is reached, the arrays expand automatically using `realloc`.
* **File Management:** Data is read from `.txt` files at program startup and updated data is saved back to the files upon exit.
* **Whitespace Support:** Supports book and author names containing spaces (e.g., "Frank Herbert") via custom delimiters.
* **Statistics & Reporting:**
    * List all categories and books.
    * Calculate average book price per category.
    * List books priced above the category average.
    * Find the most expensive book in each category.
* **Batch Updates:** Functionality to bulk update prices for books published before a specific year.

## 📂 File Structure

* `main.c`: The entry point of the program where test scenarios are executed.
* `project.c`: The source code containing all function implementations and business logic.
* `project.h`: The header file containing struct definitions and function prototypes.
* `Makefile`: The script used for compiling and running the project.
* `kategoriler.txt`: The data file storing category information.
* `kitaplar.txt`: The data file storing book information.

## ⚙️ Installation & Usage

The project is compiled using the `gcc` compiler and the `make` utility.

### 1. Compile
Open a terminal in the project directory and run the following command:

```bash
mingw32-make
# or depending on your system: make
