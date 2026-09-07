# Engineering Calculator

A terminal-based engineering calculator written in C. It evaluates mathematical expressions, stores calculation history, and renders function plots as ASCII graphics.

## Features

- Arithmetic expressions and common mathematical functions
- Degree and radian modes
- Constants such as pi and Euler's number
- Previous-result lookup with `ANS`
- Local calculation history
- ASCII function plotting
- Windows, Linux, and macOS-compatible source code

## Build

A C11 compiler and the standard math library are required.

### Make

```bash
git clone https://github.com/Alborzsfe/Engineering-Calculator.git
cd Engineering-Calculator
make
./engineering-calculator
```

### GCC directly

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic Finalcopy.c -lm -o engineering-calculator
```

On Windows, the output executable is typically `engineering-calculator.exe`.

## Usage notes

Run the program and select an option from the terminal menu. Calculation history is written to `calculator_history.txt`, which is intentionally ignored by Git.

This remains an educational expression parser. Do not use it for safety-critical or financial calculations without additional validation.

## Quality checks

Every push and pull request compiles the source on Linux with strict compiler warnings. The same build is also checked on Windows.

## License

MIT
