file(GLOB_RECURSE LILITH_CLIENT_SOURCES "*.cpp") # client.cpp, general.cpp etc. use VL_MACRO

set(LILITH_CLIENT_OUTPUT_SUBDIR Lilith_Client)

set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "" FORCE)

# Non-VM
add_executable(Lilith_Client WIN32 ${LILITH_CLIENT_SOURCES})
set_target_properties(Lilith_Client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${LILITH_CLIENT_OUTPUT_SUBDIR}/${CMAKE_BUILD_TYPE}"
    OUTPUT_NAME "Lilith_Client"
    CXX_EXTENSIONS OFF)

# VM
add_executable(Lilith_Client_vm WIN32 ${LILITH_CLIENT_SOURCES})
target_compile_definitions(Lilith_Client_vm PRIVATE USE_VL_MACRO)
target_link_libraries(Lilith_Client_vm PRIVATE vxlib64)
set_target_properties(Lilith_Client_vm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${LILITH_CLIENT_OUTPUT_SUBDIR}/${CMAKE_BUILD_TYPE}"
    OUTPUT_NAME "Lilith_Client_vm"
    CXX_EXTENSIONS OFF)

# Policy CMP0091 and MSVC runtime library should be set globally or per toolchain
# If really needed per target, use:
# target_compile_options(Lilith_Client_vm PRIVATE "/MD$<$<CONFIG:Debug>:d>")
# Or set CMAKE_MSVC_RUNTIME_LIBRARY before add_executable if it applies to all configs of this target
