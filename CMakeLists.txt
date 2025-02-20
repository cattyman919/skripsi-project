cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

project(oof VERSION 1.0
            LANGUAGES CXX
)

add_executable(${PROJECT_NAME} WIN32)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "todo"
)

if (WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE   
       # Prevents Windows.h from adding unnecessary includes    
       WIN32_LEAN_AND_MEAN  
       # Prevents Windows.h from defining min/max as macros 
       NOMINMAX 
       # define macro to change main to WinMain
       main=WinMain
    )   
endif() 


file(GLOB_RECURSE VAR_SOURCES CONFIGURE_DEPENDS src/*.cpp deps/*.cpp)

target_sources(${PROJECT_NAME} PRIVATE
        ${VAR_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        includes
        deps/imgui
        deps/imgui/backends
)

target_link_directories(${PROJECT_NAME} PRIVATE
        "lib"
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw3.dll
    OpenGL::GL
)
