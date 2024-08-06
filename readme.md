# Dirtree - v0.1.0
Simple Directory Tree Structure Generator using ASCII Art
## Why Dirtree?
Dirtree offers a visually appealing alternative to conventional directory listing tools like `tree`, `ls`, or `dir`. It allows you to generate clean, copy-and-paste-friendly ASCII art representations of your project's directory structure.

```
`-- dirtree/
    |-- CMakeLists.txt
    `-- src/
        |-- CMakeLists.txt
        `-- main.cpp 
```

## Installation

You can download the latest release from the [Releases](https://github.com/bonsall2004/dirtree/releases).

### Building from Source with CMake

To build Dirtree from source, follow these steps:

1. Create an intermediate build directory:
    ```bash
    mkdir intermediate
    ```

2. Navigate to the build directory:
    ```bash
    cd intermediate
    ```

3. Run CMake to configure the project:
    ```bash
    cmake -G "Ninja" ..
    ```

4. Build the project using CMake:
    ```bash
    cmake --build .
    ```

This process will generate the executable in `dirtree/binaries/`.

## License

Dirtree is licensed under the MIT License. See the LICENSE file for more details.
