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

# Target : auth
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
        src/console.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/public/resources/app.rc
)

target_include_directories(auth PRIVATE
        includes
)

target_link_directories(auth PRIVATE
        "lib"
)

target_link_libraries(auth PRIVATE 
    EagleVMStub
)

# Target: EagleVM
set(EagleVM_SOURCES
  src/EagleVM.cpp
  public/resources/EagleVM.rc
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
