# My Skripsi project

Project to demonstrate VxLang capabilities
- Authentication to demonstrate how dificult it is to reverse-engineer using VxLang (with & without cloud):
    - Console Auth Application
    - ImGui Auth Application
    - Qt Auth Application

- Performance Analysis: 
    - Quick Sort (Run 100 times)
    - Encryption (AES-256)
    - File Size

- Case Study: Lilith RAT Analysis

## File Size Analysis
I used fsutil to generate dummy bin file then embed it to the program. Example CLI to generate 100MB dummy bin file
```
fsutil file createnew dummy.bin 100000000
```

this data is then embed using .rc file
```
DUMMY_DATA RCDATA "dummy.bin"
```

## Build Configuration 

- Generator : CMake
- Qt : 6.8.2 (MSVC2022_64)
- OpenSSL Version: 3.4.0
- Build System : Ninja 
- Standard Library: MSVC 2022
- Compiler: clang-cl (compatible with MSVC)
- Target : Win32

### Environment Variables Setup

- CC = clang-cl
- CXX = clang-cl
- CMAKE_PREFIX_PATH = C:\Qt\6.8.3\msvc2022_64
- CMAKE_GENERATOR = Ninja
- PATH = C:\Qt\6.8.3\msvc2022_64\bin;%PATH% (add Qt bin folder to PATH environment)

## Build Step
use Developer Command Prompt for Visual Studio 2022 (Optional, not necessary with clang-cl)

Terminal : Command Prompt

```
make build
```
## FAQ

Q: Why do i get compile error?\
A: Make sure to use clang-cl compiler only (VxLang is only compatible with MSVC, not Clang or MinGW)

Q: Why do i get linking error?\
A: This error can have many causes such as lib not found, incorrect dll or lib files. The solution is to look closely in the CMakeLists.txt and the lib folder. Other reasons, might be becauses the correct version of MSVC or Qt is not installed.


## References

- [Lilith RAT](https://github.com/werkamsus/Lilith)
