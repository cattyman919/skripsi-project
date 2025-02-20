# My Skripsi project

ImGUI project to demonstrate EagleVM capabilities

## Build Configuration 

- Build System : Ninja 
- Compiler: MSVC (CLANG & MINGW is not compatible with the EagleVM library)
- Target : Win32

### Configuration Setup

Configure Environment variables for CXX and CC to be MSVC

CC_CLANG = clang.exe\
CC_MINGW = gcc.exe\
CC_MSVC = cl.exe

CXX_CLANG = clang++.exe\
CXX_MINGW = g++.exe\
CXX_MSVC = cl.exe

CC = %CC_MSVC%\
CXX = %CXX_MSVC%

## Build Step

```
mkdir bin | mkdir bin\pdb
cmake -B build
ninja -C build
cd bin
todo.exe
```
