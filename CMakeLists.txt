cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/pdb")

project(skripsi VERSION 1.0
            LANGUAGES CXX
)

add_link_options(
    /DEBUG
    /INCREMENTAL:NO
)

########### Target: Auth ##############
add_executable(auth)

target_compile_features(auth PRIVATE cxx_std_17)
set_target_properties(auth PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "auth"
)

# set_target_properties(auth PROPERTIES 
#     LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
# )

target_compile_definitions(auth PRIVATE
  "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

# file(GLOB VAR_SOURCES CONFIGURE_DEPENDS src/*.cpp)
# file(GLOB_RECURSE VAR_SOURCES_DEPS CONFIGURE_DEPENDS deps/*.cpp)

target_sources(auth PRIVATE
        src/auth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/public/resources/app.rc
)

target_include_directories(auth PRIVATE
        includes
)

target_link_directories(auth PRIVATE
        "lib"
)

target_link_libraries(auth PRIVATE 
    vxlib64
)

########### Target: Sorting ##############
set(Sorting_SOURCES
  src/sorting.cpp
)

add_executable(Sorting)
target_compile_features(Sorting PRIVATE cxx_std_17)
set_target_properties(Sorting PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "sorting"
)

target_sources(Sorting PRIVATE
    ${Sorting_SOURCES}
)

target_include_directories(Sorting PRIVATE
        "includes"
)

target_link_directories(Sorting PRIVATE
        "lib"
)

target_link_libraries(Sorting PRIVATE
    vxlib64
)

########### Target: Test ##############
set(Test_SOURCES
  src/test.cpp
  src/sdk.cpp
)

add_executable(Test)
target_compile_features(Test PRIVATE cxx_std_17)
set_target_properties(Test PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "test"
)

target_sources(Test PRIVATE
    ${Test_SOURCES}
)

target_include_directories(Test PRIVATE
        "includes"
)

target_link_directories(Test PRIVATE
        "lib"
)

target_link_libraries(Test PRIVATE
    vxlib64
)
