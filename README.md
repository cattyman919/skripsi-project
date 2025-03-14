# My Skripsi project

Project to demonstrate VxLang capabilities
- Authentication to demonstrate how dificult it is to reverse-engineer using VxLang:
    - Console Auth Application
    - ImGui Auth Application
    - Qt Auth Application
- Performance Analysis: 
    - Quick Sort
    - Encryption
    - File Size

## Build Configuration 

- Build System : Ninja 
- Compiler: Clang (clang-cl which is compatible with MSVC)
- Target : Win32

### Configuration Setup

Configure Environment variables for CXX and CC to be MSVC

CC = clang-cl\
CXX = clang-cl

## Build Step
use Developer Command Prompt for Visual Studio 2022

```
mkdir bin | mkdir bin\pdb
cmake -B build
ninja -C build
```
## FAQ

Q: Why do i get compile error?\
A: Make sure to use clang-cl compiler only (VxLang is only compatible with MSVC, not Clang or MinGW)

Q: Why do i get linking error?\
A: This error can have many causes such as lib not found, incorrect dll or lib files. The solution is to look closely in the CMakeLists.txt and the lib folder.
