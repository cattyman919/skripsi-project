cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/pdb")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

project(skripsi VERSION 1.0
            LANGUAGES CXX
)

# set(USE_VL_MACRO 1)
# add_compile_definitions(USE_VL_MACRO)

find_package(OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_link_options(
    /DEBUG
    /INCREMENTAL:NO
)

########### Target: App_ImGUI ##############
add_executable(app_imgui
)

target_compile_features(app_imgui PRIVATE cxx_std_17)

if(USE_VL_MACRO)
  set_target_properties(app_imgui PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "app_imgui_vm"
)
else()
set_target_properties(app_imgui PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "app_imgui"
)
endif()

set_target_properties(app_imgui PROPERTIES 
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
)

target_compile_definitions(app_imgui PRIVATE
  "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

file(GLOB VAR_SOURCES CONFIGURE_DEPENDS src/app_imgui/*.cpp)
file(GLOB_RECURSE VAR_SOURCES_DEPS CONFIGURE_DEPENDS deps/*.cpp)

target_sources(app_imgui PRIVATE
        ${VAR_SOURCES}
        ${VAR_SOURCES_DEPS}
        ${CMAKE_CURRENT_SOURCE_DIR}/public/resources/app.rc
)

target_include_directories(app_imgui PRIVATE
        includes
        deps
        deps/imgui
        deps/imgui/backends
)

target_link_directories(app_imgui PRIVATE
        "lib"
)

target_link_libraries(app_imgui PRIVATE 
    glfw3
    OpenGL::GL
    vxlib64
)

########### Target: App_Qt ##############
qt_add_executable(app_qt)

file(GLOB_RECURSE APP_QT_SOURCES_UI
    "src/app_qt/forms/*.ui"
)

file(GLOB_RECURSE APP_QT_SOURCES
    "includes/app_qt/*.h"
    "src/app_qt/src/*.cpp"
)

target_sources(app_qt PRIVATE
        ${APP_QT_SOURCES}
)
qt_add_ui(app_qt SOURCES ${APP_QT_SOURCES_UI})

target_link_libraries(app_qt PRIVATE Qt6::Widgets)

target_include_directories(app_qt PRIVATE
        includes
)

target_link_directories(app_qt PRIVATE
        "lib"
)

if(USE_VL_MACRO)
set_target_properties(app_qt PROPERTIES
    OUTPUT_NAME "app_qt_vm"
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
else()
set_target_properties(app_qt PROPERTIES
    OUTPUT_NAME "app_qt"
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
endif()

########### Target: Console ##############
add_executable(console)

target_compile_features(console PRIVATE cxx_std_17)

if(USE_VL_MACRO)
set_target_properties(console PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "console_vm"
)
else()
set_target_properties(console PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "console"
)
endif()

target_compile_definitions(console PRIVATE
  "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

target_sources(console PRIVATE
        src/console/auth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/public/resources/app.rc
)

target_include_directories(console PRIVATE
        includes
)

target_link_directories(console PRIVATE
        "lib"
)

target_link_libraries(console PRIVATE 
    vxlib64
)

########### Target: Console_Cloud ##############
add_executable(console_cloud)

target_compile_features(console_cloud PRIVATE cxx_std_17)

if(USE_VL_MACRO)
set_target_properties(console_cloud PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "console_cloud_vm"
)
else()
set_target_properties(console_cloud PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "console_cloud"
)
endif()

target_compile_definitions(console_cloud PRIVATE
  "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

target_sources(console_cloud PRIVATE
        src/console/auth_cloud.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/public/resources/app.rc
)

target_include_directories(console_cloud PRIVATE
        deps
        includes
)

target_link_directories(console_cloud PRIVATE
        "lib"
)

target_link_libraries(console_cloud PRIVATE 
    libcurl
    vxlib64
)

########### Target: Quick_Sort ##############
set(QUICKSORT_SOURCES
  src/performance/quick_sort.cpp
)

add_executable(QuickSort)
target_compile_features(QuickSort PRIVATE cxx_std_17)

if(USE_VL_MACRO)
set_target_properties(QuickSort PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "quick_sort_vm"
)
else()
set_target_properties(QuickSort PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "quick_sort"
)
endif()

target_sources(QuickSort PRIVATE
    ${QUICKSORT_SOURCES}
)

target_include_directories(QuickSort PRIVATE
        "includes"
)

target_link_directories(QuickSort PRIVATE
        "lib"
)

target_link_libraries(QuickSort PRIVATE
    vxlib64
)

########### Target: Encryption ##############

add_executable(Encryption)
target_compile_features(Encryption PRIVATE cxx_std_17)

if(USE_VL_MACRO)
  set_target_properties(Encryption PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "encryption_vm"
)
else()
  set_target_properties(Encryption PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "encryption"
)
endif()

target_sources(Encryption PRIVATE
    src/performance/encryption.cpp
    src/performance/aes.cpp
)

target_include_directories(Encryption PRIVATE
        "includes"
        deps
)

target_link_directories(Encryption PRIVATE
        "lib"
)

target_link_libraries(Encryption PRIVATE
    libssl
    libcrypto
    vxlib64
)

########### Target: Size ##############

add_executable(Size)
target_compile_features(Size PRIVATE cxx_std_17)

if(USE_VL_MACRO)
  set_target_properties(Size PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "size_vm"
)
else()
  set_target_properties(Size PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "size"
)
endif()

target_sources(Size PRIVATE
    src/performance/size.cpp
    src/performance/dummy.rc
)

target_include_directories(Size PRIVATE
        "includes"
)

target_link_directories(Size PRIVATE
        "lib"
)

target_link_libraries(Encryption PRIVATE
    vxlib64
)
