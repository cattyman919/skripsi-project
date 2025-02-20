# My Skripsi project

ImGUI project to demonstrate EagleVM capabilities

## Build Configuration 

- Build System : Ninja 
- Compiler: Clang
- Target : Win32

### Configuration Setup

Configure CXX and CC to be clang

CC = clang.exe
CXX = clang++.exe

## Build Step

```
mkdir bin
cmake -B build
ninja -C build
cd bin
todo.exe
```
