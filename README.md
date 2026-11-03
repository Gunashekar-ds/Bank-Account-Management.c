# Simple Calculator

A modular, clean, and robust command-line calculator written in C (C99 standard). It supports interactive menu execution, direct CLI argument calculations, error handling (e.g. division by zero, invalid input), and automated unit tests.

---

## Features

- **Standard Operations:** Addition (`+`), Subtraction (`-`), Multiplication (`*` or `x`), Division (`/`).
- **Advanced Operations:** Modulo (`%`) and Exponentiation / Power (`^`).
- **Interactive Mode:** User-friendly menu for performing repetitive calculations in the terminal.
- **Command-line Mode:** One-shot expression evaluation directly from arguments (e.g. `./bin/calculator 15 + 25`).
- **Error Handling:** Safe division/modulo by zero detection, input validation, and overflow handling.
- **Unit Testing:** Automated unit test suite with 100% pass verification.

---

## File Structure

```text
.
├── Makefile                     # Build script with compilation, test, and run targets
├── README.md                    # Project documentation and file structure
├── include/
│   └── calculator.h             # Header file with operation prototypes and status codes
├── src/
│   ├── calculator.c             # Core arithmetic engine implementation
│   └── main.c                   # Entry point supporting interactive & CLI modes
└── tests/
    └── test_calculator.c        # Automated unit testing suite
```

---

## Requirements

- GCC (GNU Compiler Collection) or compatible C99 compiler
- GNU Make
- Standard C math library (`libm`)

---

## Building the Project

To build the project executable:

```bash
make
```

This compiles source files into the `build/` directory and creates the executable `bin/calculator`.

To clean build artifacts:

```bash
make clean
```

---

## Usage

### 1. Command-Line Mode

Execute calculations directly:

```bash
./bin/calculator <number1> <operator> <number2>
```

Examples:

```bash
./bin/calculator 12 + 8        # Output: 20
./bin/calculator 25 - 7        # Output: 18
./bin/calculator 4.5 '*' 2     # Output: 9
./bin/calculator 4.5 x 2       # Output: 9
./bin/calculator 100 / 4       # Output: 25
./bin/calculator 17 '%' 5      # Output: 2
./bin/calculator 2 ^ 8         # Output: 256
```

*Note: In some shells, special characters like `*` or `%` should be escaped or quoted (`'*'`, `'%')` to prevent shell expansion.*

### 2. Interactive Mode

Run the program without arguments:

```bash
./bin/calculator
```

Or run via make:

```bash
make run
```

Interactive menu sample:

```text
========================================
           Simple Calculator
========================================
 1. Addition (+)
 2. Subtraction (-)
 3. Multiplication (*)
 4. Division (/)
 5. Modulo (%)
 6. Power (^)
 7. Exit
----------------------------------------
Enter choice (1-7): 1
Enter first number: 12.5
Enter second number: 7.5

>>> Result: 12.5 + 7.5 = 20
```

---

## Running Tests

Automated unit tests can be compiled and executed with:

```bash
make test
```

Output:

```text
Starting calculator test suite...

PASSED: test_addition_status
PASSED: test_addition_value
PASSED: test_addition_negatives
PASSED: test_subtraction_status
PASSED: test_subtraction_value
PASSED: test_subtraction_negative_result
PASSED: test_multiplication_status
...
Test Summary: 24 executed, 0 failed.
```
