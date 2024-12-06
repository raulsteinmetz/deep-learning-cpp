# Small Deep Learning Framework - Design Patterns
**Note:** This repository was developed as part of a university task. This implementation is not fully tested or guaranteed to be safe for production use. The author assumes no responsibility for issues arising from its use.

## Overview

This repository provides a small deep learning framework with the following features:
- Parsers for Json and CSV files
- DataFrame and DataLoader utility
- Neural Networks (with activation layers, backpropagation, etc)
- Loss Functions
- Simple training data visualization on terminal

## Project Structure

The project is organized as follows:

```
├── main.cpp         # application code
├── datasets         # directory containing sample datasets in CSV and JSON formats
├── samples          # examples demonstrating usage of the framework
├── docs             # documentation files (Doxygen)
├── comparison       # python code for accuracy comparison
├── framework        # core framework code
│   ├── data         # code for data manipulation, parsing, and dataframe creation/iteration
│   ├── nn           # neural network implementation
│   └── util         # training loops and terminal visualization utility
```

### Compile and Run

To compile and execute the program:

`./compile_run`

