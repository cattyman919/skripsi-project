set(TARGET_NAME "app_imgui")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_NAME}")

find_package(OpenGL REQUIRED)

include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/deps
    ${CMAKE_SOURCE_DIR}/deps/imgui
    ${CMAKE_SOURCE_DIR}/deps/imgui/backends
)

# Define a variable for the source files that are common to both executables
set(COMMON_APP_SOURCES
    main.cpp
    helper.cpp
    ${CMAKE_SOURCE_DIR}/public/resources/app.rc # resource file source
)

# Find the dependency sources (assuming these are needed by both login implementations)
file(GLOB_RECURSE VAR_SOURCES_DEPS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/deps/*.cpp)

# --- Define the first executable (Standard Login) ---
add_executable(${TARGET_NAME}
    ${COMMON_APP_SOURCES}
    login.cpp # Specific source file for this executable
    ${VAR_SOURCES_DEPS} # Include dependency sources
)

# --- Define the second executable (Cloud Login) ---
add_executable(${TARGET_NAME}_cloud
    ${COMMON_APP_SOURCES}
    login_cloud.cpp # Specific source file for this executable
    ${VAR_SOURCES_DEPS} # Include dependency sources
)

# Compile Definitions (applied to both targets)
target_compile_definitions(${TARGET_NAME} PRIVATE
    "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)
target_compile_definitions(${TARGET_NAME}_cloud PRIVATE
    "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

# Linked Libraries (applied to both targets)
target_link_libraries(${TARGET_NAME} PRIVATE
    glfw3
    OpenGL::GL 
    vxlib64    
)

target_link_libraries(${TARGET_NAME}_cloud PRIVATE
    glfw3
    OpenGL::GL
    vxlib64
    libcurl
)

set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" # Windows-specific
)

set_target_properties(${TARGET_NAME}_cloud PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" # Windows-specific
)

if(USE_VL_MACRO)
  set_target_properties(${TARGET_NAME} PROPERTIES
        OUTPUT_NAME "${TARGET_NAME}_vm"
  )
  set_target_properties(${TARGET_NAME}_cloud PROPERTIES
        OUTPUT_NAME "${TARGET_NAME}_cloud_vm" # Maybe add "_cloud" to the output name
  )

else()
  set_target_properties(${TARGET_NAME} PROPERTIES
        OUTPUT_NAME "${TARGET_NAME}"
  )
  
  set_target_properties(${TARGET_NAME}_cloud PROPERTIES
        OUTPUT_NAME "${TARGET_NAME}_cloud"
  )
endif()

