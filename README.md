# Ray Tracing In C++

A minimal ray tracing renderer implemented in C++ using SDL2 for window management and pixel rendering.

This project demonstrates the core fundamentals of ray tracing, including ray-object intersection and basic lighting calculations. It is designed as a learning-focused implementation with a clean and straightforward structure.

---

## Overview

This project renders a simple 3D scene using ray tracing techniques. Rays are cast from the camera into the scene to determine object intersections and compute pixel colors based on lighting.

The primary goal of this repository is educational: to understand how ray tracing works at a low level while integrating external libraries such as SDL2 in C++.

---

## Features

- Ray–sphere intersection
- Basic diffuse lighting model
- Real-time rendering using SDL2
- Structured and readable C++ implementation
- Makefile-based build system
- Compatible with MinGW (Windows) and standard g++ toolchains

---

## Requirements

Ensure the following are installed before building:

- C++ compiler (g++ with C++17 support recommended)
- SDL2 development libraries
- Make utility

---

## Build Instructions

### Using the Makefile

From the root directory of the project:

```bash
mingw32-make
```

This will compile the project and generate an executable named:

```bash
main.exe
```

To run the program:

```bash
./main
```

---

### Manual Compilation (Windows / MinGW)

If you prefer to compile manually:

```bash
g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
```

Ensure that:

- SDL2 header files are located inside `src/Include`
- SDL2 library files are located inside `src/lib`
- The required SDL2 `.dll` file is placed in the same directory as the executable

---

### Linux / macOS (Global SDL2 Installation)

If SDL2 is installed system-wide:

```bash
g++ main.cpp $(sdl2-config --cflags --libs) -o main
```

---

## Project Structure

```
Ray-Tracing-In-Cpp/
│
├── src/
│   ├── Include/      # SDL2 header files
│   └── lib/          # SDL2 library files
│
├── main.cpp
├── Makefile
└── README.md
```

---

## Learning Objectives

By exploring this project, you will understand:

- The mathematical foundation of ray tracing
- Ray-object intersection algorithms
- Basic lighting computation
- Pixel-level rendering using SDL2
- Linking third-party libraries in C++

---

## Author

Jay Rathore

---

## License

This project is open-source and available for educational and personal use.