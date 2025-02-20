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
# Target : Todo
add_executable(todo WIN32)

target_compile_features(todo PRIVATE cxx_std_17)
set_target_properties(todo PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "todo"
)

if (WIN32)
  target_compile_definitions(todo PRIVATE   
       # Prevents Windows.h from adding unnecessary includes    
       WIN32_LEAN_AND_MEAN  
       # Prevents Windows.h from defining min/max as macros 
       NOMINMAX 
       # define macro to change main to WinMain
       main=WinMain
    )   
endif() 

file(GLOB_RECURSE VAR_SOURCES CONFIGURE_DEPENDS src/main.cpp deps/*.cpp)

target_sources(todo PRIVATE
        ${VAR_SOURCES}
)

target_include_directories(todo PRIVATE
        includes
        deps/imgui
        deps/imgui/backends
)

target_link_directories(todo PRIVATE
        "lib"
)

find_package(OpenGL REQUIRED)

target_link_libraries(todo PRIVATE 
    glfw3
    OpenGL::GL
)

# Target: EagleVM
set(EagleVM_SOURCES
  "src/EagleVM/EagleVM.cpp"
)

add_executable(EagleVM)

target_sources(EagleVM PRIVATE ${EagleVM_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EagleVM_SOURCES})

target_compile_features(EagleVM PRIVATE
	cxx_std_23
)

target_include_directories(EagleVM PRIVATE
        "includes"
        "deps"
)

target_link_directories(EagleVM PRIVATE
        "lib"
)

target_link_libraries(EagleVM PRIVATE
	EagleVMCore
 	Zycore
	Zydis
	spdlog
)

get_directory_property(CMKR_VS_STARTUP_PROJECT DIRECTORY ${PROJECT_SOURCE_DIR} DEFINITION VS_STARTUP_PROJECT)
if(NOT CMKR_VS_STARTUP_PROJECT)
	set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EagleVM)
endif()


# Target: EagleVMSandbox
set(EagleVMSandbox_SOURCES
  "src/EagleVMSandbox/EagleVMSandbox.cpp"
)

add_executable(EagleVMSandbox)

target_sources(EagleVMSandbox PRIVATE ${EagleVMSandbox_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EagleVMSandbox_SOURCES})

target_compile_features(EagleVMSandbox PRIVATE
	cxx_std_23
)
target_include_directories(EagleVMSandbox PRIVATE
        "includes"
)

target_link_libraries(EagleVMSandbox PRIVATE
	EagleVMStub
)
target_link_directories(EagleVMSandbox
    PRIVATE
    "lib"
)
