include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/deps) # For nlohmann/json if used by cloud.hpp

set(CONSOLE_RC_FILE ${CMAKE_SOURCE_DIR}/public/resources/app.rc) # or console.rc if specific
set(CONSOLE_DEFINITIONS "SOURCE_ROOT=${CMAKE_SOURCE_DIR}")

add_project_executables(console
    OUTPUT_SUBDIR console
    SOURCES console.cpp
    CLOUD_SOURCES console_cloud.cpp
    RC_FILE ${CONSOLE_RC_FILE}
    DEFINITIONS ${CONSOLE_DEFINITIONS}
    NON_VM_LIBS # No specific non-VM libs beyond standard
    VM_LIBS vxlib64
    CLOUD_NON_VM_LIBS libcurl
    CLOUD_VM_LIBS vxlib64 libcurl
)
