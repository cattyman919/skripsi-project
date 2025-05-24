cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Ensure CMAKE_BUILD_TYPE is set, default to Release if not.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "CMAKE_BUILD_TYPE not set, defaulting to Release.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Aggressive Optimization to More Optimization O3 -> O2
string(REPLACE "-O3" "-O0" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
string(REPLACE "-O2" "-O0" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "")
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/pdb/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(skripsi VERSION 1.0
            LANGUAGES CXX
)

# if(USE_VL_MACRO)
#   message(STATUS "VL Macro enabled via USE_VL_MACRO option.")
#   add_compile_definitions(USE_VL_MACRO) # Add the definition so that VxLang is active
# else()
#   message(STATUS "VL Macro disabled via USE_VL_MACRO option.")
# endif()

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)
if(MSVC)
  add_link_options(
      "/DEBUG:NONE" # Typically no debug info in final release link
      "/INCREMENTAL:NO"
  )

  add_link_options(
    $<$<CONFIG:Debug>:/DEBUG>
  )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/includes
)

# Helper function to define pairs of executables
function(add_project_executables BASE_TARGET_NAME)
    set(options IS_GUI_APP) # Add IS_GUI_APP as a boolean option
    set(oneValueArgs OUTPUT_SUBDIR)
    set(multiValueArgs SOURCES COMMON_SOURCES CLOUD_SOURCES RC_FILE NON_VM_LIBS VM_LIBS CLOUD_NON_VM_LIBS CLOUD_VM_LIBS DEFINITIONS)
    cmake_parse_arguments(TARGET "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(OUTPUT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/${TARGET_OUTPUT_SUBDIR}/${CMAKE_BUILD_TYPE}")

    # --- Standard Target ---
    if(TARGET_SOURCES OR TARGET_COMMON_SOURCES) # Check if there are any sources
        set(WIN32_ARG "")
        if(MSVC AND TARGET_IS_GUI_APP)
            set(WIN32_ARG WIN32) # Use WIN32 arg for add_executable for GUI apps
        endif()

        add_executable(${BASE_TARGET_NAME} ${WIN32_ARG} ${TARGET_COMMON_SOURCES} ${TARGET_SOURCES} ${TARGET_RC_FILE})
        target_link_libraries(${BASE_TARGET_NAME} PRIVATE ${TARGET_NON_VM_LIBS})
        target_compile_definitions(${BASE_TARGET_NAME} PRIVATE ${TARGET_DEFINITIONS})
        set_target_properties(${BASE_TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR}"
            OUTPUT_NAME "${BASE_TARGET_NAME}"
            CXX_EXTENSIONS OFF)
        if(MSVC AND TARGET_IS_GUI_APP AND TARGET_RC_FILE) # RC_FILE check might be redundant if WIN32_ARG handles entry
            set_target_properties(${BASE_TARGET_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        elseif(MSVC) # For console apps, ensure subsystem is console
             set_target_properties(${BASE_TARGET_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
        endif()

        # --- VM Target ---
        add_executable(${BASE_TARGET_NAME}_vm ${WIN32_ARG} ${TARGET_COMMON_SOURCES} ${TARGET_SOURCES} ${TARGET_RC_FILE})
        target_compile_definitions(${BASE_TARGET_NAME}_vm PRIVATE USE_VL_MACRO ${TARGET_DEFINITIONS})
        target_link_libraries(${BASE_TARGET_NAME}_vm PRIVATE ${TARGET_VM_LIBS})
        set_target_properties(${BASE_TARGET_NAME}_vm PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR}"
            OUTPUT_NAME "${BASE_TARGET_NAME}_vm"
            CXX_EXTENSIONS OFF)
        if(MSVC AND TARGET_IS_GUI_APP AND TARGET_RC_FILE)
             set_target_properties(${BASE_TARGET_NAME}_vm PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        elseif(MSVC)
             set_target_properties(${BASE_TARGET_NAME}_vm PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
        endif()
    endif()

    # --- Cloud Target ---
    if(TARGET_CLOUD_SOURCES OR TARGET_COMMON_SOURCES)
        set(WIN32_ARG_CLOUD "")
        if(MSVC AND TARGET_IS_GUI_APP) # Assume cloud variant of GUI app is also GUI
            set(WIN32_ARG_CLOUD WIN32)
        endif()

        add_executable(${BASE_TARGET_NAME}_cloud ${WIN32_ARG_CLOUD} ${TARGET_COMMON_SOURCES} ${TARGET_CLOUD_SOURCES} ${TARGET_RC_FILE})
        target_link_libraries(${BASE_TARGET_NAME}_cloud PRIVATE ${TARGET_CLOUD_NON_VM_LIBS})
        target_compile_definitions(${BASE_TARGET_NAME}_cloud PRIVATE ${TARGET_DEFINITIONS})
        set_target_properties(${BASE_TARGET_NAME}_cloud PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR}"
            OUTPUT_NAME "${BASE_TARGET_NAME}_cloud"
            CXX_EXTENSIONS OFF)
        if(MSVC AND TARGET_IS_GUI_APP AND TARGET_RC_FILE)
            set_target_properties(${BASE_TARGET_NAME}_cloud PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        elseif(MSVC)
            set_target_properties(${BASE_TARGET_NAME}_cloud PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
        endif()

        # --- Cloud VM Target ---
        add_executable(${BASE_TARGET_NAME}_cloud_vm ${WIN32_ARG_CLOUD} ${TARGET_COMMON_SOURCES} ${TARGET_CLOUD_SOURCES} ${TARGET_RC_FILE})
        target_compile_definitions(${BASE_TARGET_NAME}_cloud_vm PRIVATE USE_VL_MACRO ${TARGET_DEFINITIONS})
        target_link_libraries(${BASE_TARGET_NAME}_cloud_vm PRIVATE ${TARGET_CLOUD_VM_LIBS})
        set_target_properties(${BASE_TARGET_NAME}_cloud_vm PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR}"
            OUTPUT_NAME "${BASE_TARGET_NAME}_cloud_vm"
            CXX_EXTENSIONS OFF)
        if(MSVC AND TARGET_IS_GUI_APP AND TARGET_RC_FILE)
            set_target_properties(${BASE_TARGET_NAME}_cloud_vm PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        elseif(MSVC)
            set_target_properties(${BASE_TARGET_NAME}_cloud_vm PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
        endif()
    endif()
endfunction()

########### Targets ##############

add_subdirectory(src/app_imgui)
add_subdirectory(src/app_qt)
add_subdirectory(src/console)
add_subdirectory(src/performance)
add_subdirectory(src/malwares/Lilith/client)
add_subdirectory(src/malwares/Lilith/server)
add_subdirectory(src/malwares/JuicyPotato)
