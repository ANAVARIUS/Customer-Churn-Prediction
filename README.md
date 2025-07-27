# Customer Churn Predictor

Customer Churn Predictor is a C++ project that implements a simple logistic regression model to predict whether a customer is likely to cancel a service or subscription, based on a set of input features.

## Key Implementations

- Manual implementation of core vector and matrix operations
- Logistic Regression algorithm with sigmoid activation
- Cross-Entropy Loss for classification accuracy
- Gradient Descent optimization implemented from scratch
- Basic CSV parsing for input and output handling

## How to Build and Run

### Prerequisites

- A C++20-compliant compiler (e.g., g++)
- make utility

### Build the Project

```bash
make
```

This compiles the main application and produces an executable named `logistic_churn`.

### Run the Program

```bash
./logistic_churn
```

Make sure your dataset and required files are placed in the expected locations or passed accordingly if applicable.

### Run the Unit Tests

```bash
make test
```

This builds and runs the test suite using the files in the `tests/` directory.

### Clean Build Files

```bash
make clean
```

This removes the executables (`logistic_churn`, `run_tests`) from the project directory.

## Project Structure

```
.
├── main.cpp          # Entry point
├── include/          # Header files
│   └── ...
├── src/              # Core logic (vector ops, model, etc.)
│   └── ...
├── cli/              # Command line interface
├── data/             # Input and output data
├── logs/             # Execution logs
├── tests/            # Unit tests
├── Makefile          # Build and test automation
└── README.md         # Project documentation
```

## Project Status

**This project is in early development and may not be fully functional yet.**

Core components are still being implemented and integrated. Expect incomplete features and possible runtime issues.
