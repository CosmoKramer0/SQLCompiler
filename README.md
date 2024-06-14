# SQL Analyzer and Intermediate Code Generator

This project consists of a Lexical Analyzer, Syntax Analyzer, and Intermediate Code Generator for SQL SELECT statements, implemented in C. The components analyze a given SQL query and generate intermediate code based on it.

## Project Structure

- `Query.txt`: Contains the SQL query to be analyzed.
- `Grammar.txt`: Defines the grammar for the SQL SELECT statement.
- `LA4SQL.c`: Lexical Analyzer that tokenizes the SQL query from `Query.txt`.
- `SA4SQL.c`: Syntax Analyzer that validates the syntax of the SQL query from `Query.txt`.
- `ICG4SQL.c`: Intermediate Code Generator that produces intermediate code for the SQL query from `Query.txt`.
- `lexical_analysis_output.txt`: Output file of the Lexical Analyzer.
- `syntax_analysis_output.txt`: Output file of the Syntax Analyzer.
- `intermediate_code_output.txt`: Output file of the Intermediate Code Generator.

## Prerequisites

- C compiler (e.g., GCC)
- Compiler Design concepts

## Running the Project

### 1. Lexical Analysis

The Lexical Analyzer tokenizes the SQL query present in `Query.txt`.

**Compile and run the Lexical Analyzer:**
```bash
  gcc -o LA4SQL LA4SQL.c
  ./LA4SQL
```
**Output:** The tokens are saved in `lexical_analysis_output.txt`.

### 2. Syntax Analysis

The Syntax Analyzer validates the syntax of the SQL query present in Query.txt.

**Compile and run the Syntax Analyzer:**
```bash
  gcc -o SA4SQL SA4SQL.c
  ./SA4SQL
```
**Output:** The result of the syntax analysis is saved in `syntax_analysis_output.txt`.

### 3. Intermediate Code Generation

The Intermediate Code Generator produces intermediate code for the SQL query present in `Query.txt`.

**Compile and run the Intermediate Code Generator:**
```bash
  gcc -o ICG4SQL ICG4SQL.c
  ./ICG4SQL
```
**Output:** The generated intermediate code is saved in `intermediate_code_output.txt`.

## Contact
For questions or feedback, please contact fahadbaig247@gmail.com.

