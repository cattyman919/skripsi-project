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
    EagleVMStub
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
    EagleVMStub
)

########### Target: Test ##############
add_executable(Test)
target_compile_features(Test PRIVATE cxx_std_17)
set_target_properties(Test PROPERTIES 
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "test"
)

target_sources(Test PRIVATE
    src/test.cpp
)

target_include_directories(Test PRIVATE
        "includes"
)

target_link_directories(Test PRIVATE
        "lib"
)

target_link_libraries(Test PRIVATE
    EagleVMStub
)

########### Target: EagleVM_auth ##############
set(EagleVM_auth_SOURCES
  src/EagleVM/EagleVM_auth.cpp
  public/resources/EagleVM.rc
)

add_executable(EagleVM_auth)

target_sources(EagleVM_auth PRIVATE ${EagleVM_auth_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EagleVM_auth_SOURCES})

target_compile_features(EagleVM_auth PRIVATE
	cxx_std_23
)

target_include_directories(EagleVM_auth PRIVATE
        "includes"
        "deps"
)

target_link_directories(EagleVM_auth PRIVATE
        "lib"
)

target_link_libraries(EagleVM_auth PRIVATE
	EagleVMCore
 	Zycore
	Zydis
	spdlog
)

get_directory_property(CMKR_VS_STARTUP_PROJECT DIRECTORY ${PROJECT_SOURCE_DIR} DEFINITION VS_STARTUP_PROJECT)
if(NOT CMKR_VS_STARTUP_PROJECT)
  set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EagleVM_auth)
endif()


########### Target: EagleVM_sorting ##############
set(EagleVM_sorting_SOURCES
  src/EagleVM/EagleVM_sorting.cpp
  public/resources/EagleVM.rc
)

add_executable(EagleVM_sorting)

target_sources(EagleVM_sorting PRIVATE ${EagleVM_sorting_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EagleVM_sorting_SOURCES})

target_compile_features(EagleVM_sorting PRIVATE
	cxx_std_23
)

target_include_directories(EagleVM_sorting PRIVATE
        "includes"
        "deps"
)

target_link_directories(EagleVM_sorting PRIVATE
        "lib"
)

target_link_libraries(EagleVM_sorting PRIVATE
	EagleVMCore
 	Zycore
	Zydis
	spdlog
)

get_directory_property(CMKR_VS_STARTUP_PROJECT DIRECTORY ${PROJECT_SOURCE_DIR} DEFINITION VS_STARTUP_PROJECT)
if(NOT CMKR_VS_STARTUP_PROJECT)
  set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EagleVM_sorting)
endif()

########### Target: EagleVM_test ##############
set(EagleVM_test_SOURCES
  src/EagleVM/EagleVM_test.cpp
  public/resources/EagleVM.rc
)

add_executable(EagleVM_test)

target_sources(EagleVM_test PRIVATE ${EagleVM_test_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EagleVM_test_SOURCES})

target_compile_features(EagleVM_test PRIVATE
	cxx_std_23
)

target_include_directories(EagleVM_test PRIVATE
        "includes"
        "deps"
)

target_link_directories(EagleVM_test PRIVATE
        "lib"
)

target_link_libraries(EagleVM_test PRIVATE
	EagleVMCore
 	Zycore
	Zydis
	spdlog
)

get_directory_property(CMKR_VS_STARTUP_PROJECT DIRECTORY ${PROJECT_SOURCE_DIR} DEFINITION VS_STARTUP_PROJECT)
if(NOT CMKR_VS_STARTUP_PROJECT)
  set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EagleVM_test)
endif()
