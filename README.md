# CMake_Library_Template
A template repository to showcase how to properly set up a library with CMake

## Building with CMake

To build the static library, run the following commands:

```bash
cmake -S . -B build
cmake --build build
```

To build a shared libary, run the following commands:

```bash
cmake -S . -B build -DBUILD_SHARED_LIBS=ON
cmake --build build
```

### Installing the library

To install the library, run the following command:

```bash
cmake --install build
```