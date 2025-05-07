cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/pdb")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(skripsi VERSION 1.0
            LANGUAGES CXX
)

# set(USE_VL_MACRO 1)
# add_compile_definitions(USE_VL_MACRO)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

add_link_options(
    /DEBUG
    /INCREMENTAL:NO
)

include_directories(
    ${CMAKE_SOURCE_DIR}/includes
)

########### Targets ##############

add_subdirectory(src/app_imgui)
add_subdirectory(src/app_qt)
add_subdirectory(src/console)
add_subdirectory(src/performance)
add_subdirectory(src/Lilith/client)
add_subdirectory(src/Lilith/server)
