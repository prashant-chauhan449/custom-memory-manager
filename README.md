# Custom Memory Manager Simulator

A memory management simulator developed using pure C.

## Overview

This project simulates dynamic memory allocation and deallocation within a fixed 1024-byte memory pool.

It implements different memory allocation strategies and manages memory blocks using an array of structures.

## Features

- Dynamic memory pool initialization using `malloc()`
- First Fit allocation strategy
- Best Fit allocation strategy
- Worst Fit allocation strategy
- Memory allocation and deallocation
- Memory block splitting
- Adjacent free block merging
- Allocation ID management
- Memory layout visualization
- Memory usage statistics
- External fragmentation calculation

## Technologies

- C Programming Language
- GCC Compiler
- Standard C Library

## Compilation

```bash
gcc main.c memory_manager.c allocation.c deallocation.c display.c -o memory_manager
```

## Run

```bash
./memory_manager
```

## Memory Pool

Total memory pool size: 1024 bytes.

## Author

Prashant Kumar