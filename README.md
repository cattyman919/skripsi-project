# VxLang Demonstration Project (Skripsi)

This project serves as a demonstration of VxLang's capabilities in software protection and its impact on application performance. It includes various applications and benchmarks designed to showcase different aspects of VxLang.

## Project Goals

*   **Reverse Engineering Deterrence:** Demonstrate the increased difficulty of reverse-engineering applications protected by VxLang, with and without cloud-based authentication.
*   **Performance Analysis:** Analyze the performance overhead introduced by VxLang virtualization on common computational tasks and application size.
*   **Case Study:** Provide a practical example of analyzing a (simulated) protected application (Lilith RAT).

## Features & Demonstrations

The project is divided into several key components:

1.  **Authentication Examples:**
    *   **Purpose:** To showcase how VxLang can protect authentication mechanisms.
    *   **Applications:**
        *   Console Authentication Application
        *   ImGui-based Authentication Application
        *   Qt-based Authentication Application
    *   **Variants:** Each authentication application has two versions:
        *   **Standard:** Local authentication logic.
        *   **Cloud-Integrated:** Authentication logic relies on a backend server.
    *   **Builds:** Each variant is built as:
        *   A non-virtualized executable (e.g., `console.exe`, `app_qt_cloud.exe`).
        *   A VxLang-virtualized executable (e.g., `console_vm.exe`, `app_qt_cloud_vm.exe`).

2.  **Performance Analysis Benchmarks:**
    *   **Purpose:** To measure and compare the performance of common algorithms and executable size with and without VxLang virtualization.
    *   **Benchmarks:**
        *   **Quick Sort:** Sorting a large array of integers (run multiple times for averaging).
        *   **AES-256 Encryption:** Encrypting and decrypting a significant amount of data.
        *   **File Size Analysis:** Examining the executable size, including embedded resources.
    *   **Builds:** Each benchmark is built as a non-virtualized and a VxLang-virtualized executable.

3.  **Case Study: Lilith RAT Analysis**
    *   **Purpose:** A simulated Remote Administration Tool (RAT) to provide a more complex application for protection and analysis.
    *   **Components:**
        *   `Lilith_Client_vm.exe`: The VxLang-virtualized client.
        *   `Lilith_Server.exe`: The non-virtualized server component.

## File Size Analysis Detail

To analyze the impact on file size, particularly with embedded resources, the `size` benchmark includes a large (100MB) dummy binary file.
This file is generated using `fsutil` (if it doesn't exist) during the `make dummy` or initial `make configure` step:
```bash
fsutil file createnew src/performance/dummy.bin 100000000
```

This dummy.bin is then embedded into the size.exe and size_vm.exe executables via a resource file (dummy.rc):
```DUMMY_DATA RCDATA "dummy.bin"```

## Build Configuration 

- Operating System: Windows (project heavily relies on Windows-specific features and tools).
- Compiler: clang-cl (ensure it's installed and in your PATH, or use Developer Command Prompt). It must be compatible with MSVC 2022.
- CMake: Version 3.21 or higher.
- Build System Generator: Ninja (ensure ninja.exe is in your PATH).
- Qt Version: Qt 6.8.2 (MSVC2022_64). The CMAKE_PREFIX_PATH must point to this installation.
- OpenSSL Version: 3.4.0 (headers in deps/openssl, libraries in lib/).
- VxLang: The VxLang executable (vxlang/vxlang.exe) and its license file (vxlang/vxlang.vxm) must be present in the vxlang directory.
- Standard Library: MSVC 2022.
- Docker & Docker Compose : Required for running the cloud backend service (make cloud).
- (Recommended) Visual Studio 2022: Using the "Developer Command Prompt for VS 2022" is highly recommended as it sets up the necessary environment for clang-cl to work with the MSVC toolchain and SDKs.

### Environment Variables Setup

- CC = clang-cl
- CXX = clang-cl
- CMAKE_PREFIX_PATH = C:\Qt\6.8.3\msvc2022_64
- CMAKE_PREFIX_PATH: Set this to your Qt MSVC2022_64 installation directory.
    - Example: set CMAKE_PREFIX_PATH=C:\Qt\6.8.2\msvc2022_64 (for Command Prompt)
    - Example: $env:CMAKE_PREFIX_PATH = "C:\Qt\6.8.2\msvc2022_64" (for PowerShell)
- CMAKE_GENERATOR = Ninja
- PATH:
    - Ensure your Qt installation's bin directory (e.g., C:\Qt\6.8.2\msvc2022_64\bin) is in your PATH.
    - Ensure the directory containing clang-cl.exe and lld-link.exe (usually LLVM's bin directory) is in your PATH if not using the Developer Command Prompt.
    - Ensure the directory containing ninja.exe is in your PATH.

## Build Step
It is highly recommended to use the "Developer Command Prompt for VS 2022" for these steps, as it pre-configures much of the MSVC environment that clang-cl utilizes.

1. Clone the Repository:
2. Set Up Environment Variables:
Configure the environment variables as described in the "Environment Variables Setup" section in your chosen terminal.
3. Generate Dummy File (for size benchmark):
This step is usually handled automatically by make configure or any make command if src/performance/dummy.bin is missing. You can also run it manually:
4. Configure CMake (One-time, or when CMakeLists.txt changes):
5. Build Executables:
You have several options using the Makefile:
    - Build Everything (Recommended for full demonstration):
    Compiles all non-VM targets, all VM targets, and then runs virtualize.bat to process the VM executables with VxLang.
    ```
    make # For Release build (default)
    make BUILD_TYPE=Debug # For Debug build
    ```
    - Build Only Non-Virtualized Executables:
    ```
    make build
    make build BUILD_TYPE=Debug
    ```
    - Build Only Virtualized Executables (before VxLang processing):
    This compiles the *_vm.exe files but does not run vxlang.exe on them.
    ```
    make build_vm_executables
    make build_vm_executables BUILD_TYPE=Debug
    ```
    - Build Virtualized Executables and Run VxLang:
    This is equivalent to make build_vm_executables followed by running virtualize.bat.
    ```
    make build_vm
    make build_vm BUILD_TYPE=Debug
    ```
    - Re-run VxLang on Existing VM Executables:
    If you've already built the *_vm.exe files and only want to re-apply VxLang (e.g., after changing VxLang settings or virtualize.bat). This will delete previous .vxm.exe files.
    ```
    make rebuild_vm
    ```
6. Run Cloud Backend (Optional, for cloud-enabled apps):
This requires Docker and Docker Compose to be installed and running.
```
make cloud
```
7. Deploy Qt Applications (Important for Release builds):
For the Qt applications (app_qt, app_qt_cloud, and their _vm variants) to run outside the build environment, especially Release builds, you need to deploy their Qt dependencies (DLLs, plugins).
Navigate to the output directory and use windeployqt:
```
cd bin/app_qt/Release # Or Debug if you built that
windeployqt .
```
## Project Structure Overview
- src/: Contains the source code for the different application modules.
    - app_imgui/: ImGui-based authentication application.
    - app_qt/: Qt-based authentication application.
    - console/: Console-based authentication application.
    - performance/: Performance benchmark applications.
    - Lilith/: Lilith RAT case study (client and server).
- includes/: Shared C++ header files for the applications.
- lib/: Pre-compiled third-party libraries (e.g., vxlib64.lib, libcurl.lib, OpenSSL libs).
- deps/: Source code for some third-party dependencies (e.g., ImGui headers, nlohmann/json, OpenSSL headers).
- public/: Static resources like icons (.ico) and fonts (.ttf).
- bin/: Output directory for all compiled executables, organized by module and build type (e.g., bin/console/Release/console.exe).
- build/: CMake and Ninja intermediate build files. Can be safely deleted.
- server/: Contains the Docker configuration and backend source code for the cloud services.
- vxlang/: Contains the vxlang.exe protector and its license file vxlang.vxm.
- Makefile: Main build orchestration script.
- CMakeLists.txt: Top-level CMake configuration file.

## FAQ

- Q: I get compile errors like "cannot open source file" or "library not found."
    - A1: Ensure you are using the "Developer Command Prompt for VS 2022" or have correctly set up your PATH, INCLUDE, and LIB environment variables for clang-cl and the MSVC toolchain.
    - A2: Verify that CMAKE_PREFIX_PATH is correctly set to your Qt 6 MSVC 64-bit installation.
    - A3: Make sure vxlang/vxlang.exe, vxlang/vxlang.vxm, and all libraries in the lib/ folder are present.

- Q: I get linking errors, especially with vxlib64.lib or other specific libraries.
    - A1: Double-check that the lib/ directory contains all necessary .lib files and that link_directories(${CMAKE_SOURCE_DIR}/lib) is present in the top-level CMakeLists.txt.
    - A2: Ensure you are consistently building for 64-bit if using 64-bit libraries (this project is configured for 64-bit).

- Q: console.exe or quick_sort.exe (or other console apps) crash immediately.
    - A: This usually means they were incorrectly linked as /SUBSYSTEM:WINDOWS applications. The add_project_executables CMake function and target definitions should now correctly handle this by ensuring console apps are linked with /SUBSYSTEM:CONSOLE. If this persists, clean your build directory (make clean then make configure) and rebuild.

- Q: Qt applications show MOC-related linking errors (undefined metaObject, qt_metacall, etc.).
    - A: Ensure CMAKE_AUTOMOC ON is set in src/app_qt/CMakeLists.txt. Also, make sure headers containing Q_OBJECT are either directly included by .cpp files added to qt_add_executable or are themselves listed in qt_add_executable. The include_directories(${CMAKE_SOURCE_DIR}/includes) in src/app_qt/CMakeLists.txt is also crucial for AUTOMOC to find the headers.

- Q: virtualize.bat reports that *_vm.exe does not exist.
    - A: Ensure that make build_vm_executables (or make build_vm, or make) completed successfully for the specific target. Check the bin/<target_name>/<BUILD_TYPE>/ directory. Also, ensure build_type in virtualize.bat matches the BUILD_TYPE used for the make command (default is Release).

- Q: make dummy or fsutil fails.
    - A: Ensure you have permissions to write to the src/performance/ directory. fsutil is a Windows command; this step will fail on other OSes.

## References

- [Lilith RAT](https://github.com/werkamsus/Lilith)
