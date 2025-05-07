file(GLOB_RECURSE SOURCES "*.cpp")

set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(Lilith_Client WIN32 ${SOURCES})
