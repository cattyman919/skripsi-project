set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/deps) # for nlohmann/json via cloud.hpp

set(APP_QT_OUTPUT_SUBDIR app_qt)
set(APP_QT_RC_FILE ${CMAKE_SOURCE_DIR}/public/resources/qt.rc)

file(GLOB_RECURSE APP_QT_HEADERS
    "${CMAKE_SOURCE_DIR}/includes/app_qt/*.h"
)
file(GLOB_RECURSE APP_QT_SOURCES_UI "forms/*.ui")

set(COMMON_QT_SOURCES
    src/main.cpp
    src/todo.cpp
    ${APP_QT_HEADERS}
)

set(OUTPUT_BASE_DIR_QT "${CMAKE_SOURCE_DIR}/bin/${APP_QT_OUTPUT_SUBDIR}/${CMAKE_BUILD_TYPE}")

# --- app_qt (non-cloud) ---
set(TARGET_QT_BASE app_qt)

# Non-VM
qt_add_executable(${TARGET_QT_BASE} WIN32 # Pass WIN32 as a keyword
    ${COMMON_QT_SOURCES}
    src/todo_auth.cpp
    ${APP_QT_RC_FILE}
)
qt_add_ui(${TARGET_QT_BASE} SOURCES ${APP_QT_SOURCES_UI})
target_link_libraries(${TARGET_QT_BASE} PRIVATE Qt6::Widgets)
set_target_properties(${TARGET_QT_BASE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR_QT}"
    OUTPUT_NAME "${TARGET_QT_BASE}"
    MACOSX_BUNDLE OFF # Set MACOSX_BUNDLE as a property
)

# VM
qt_add_executable(${TARGET_QT_BASE}_vm WIN32 # Pass WIN32 as a keyword
    ${COMMON_QT_SOURCES}
    src/todo_auth.cpp
    ${APP_QT_RC_FILE}
)
qt_add_ui(${TARGET_QT_BASE}_vm SOURCES ${APP_QT_SOURCES_UI})
target_compile_definitions(${TARGET_QT_BASE}_vm PRIVATE USE_VL_MACRO)
target_link_libraries(${TARGET_QT_BASE}_vm PRIVATE Qt6::Widgets vxlib64)
set_target_properties(${TARGET_QT_BASE}_vm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR_QT}"
    OUTPUT_NAME "${TARGET_QT_BASE}_vm"
    MACOSX_BUNDLE OFF # Set MACOSX_BUNDLE as a property
)


# --- app_qt_cloud ---
set(TARGET_QT_CLOUD_BASE app_qt_cloud)

# Non-VM Cloud
qt_add_executable(${TARGET_QT_CLOUD_BASE} WIN32 # Pass WIN32 as a keyword
    ${COMMON_QT_SOURCES}
    src/todo_auth_cloud.cpp
    ${APP_QT_RC_FILE}
)
qt_add_ui(${TARGET_QT_CLOUD_BASE} SOURCES ${APP_QT_SOURCES_UI})
target_link_libraries(${TARGET_QT_CLOUD_BASE} PRIVATE Qt6::Widgets libcurl)
set_target_properties(${TARGET_QT_CLOUD_BASE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR_QT}"
    OUTPUT_NAME "${TARGET_QT_CLOUD_BASE}"
    MACOSX_BUNDLE OFF # Set MACOSX_BUNDLE as a property
)


# VM Cloud
qt_add_executable(${TARGET_QT_CLOUD_BASE}_vm WIN32 # Pass WIN32 as a keyword
    ${COMMON_QT_SOURCES}
    src/todo_auth_cloud.cpp
    ${APP_QT_RC_FILE}
)
qt_add_ui(${TARGET_QT_CLOUD_BASE}_vm SOURCES ${APP_QT_SOURCES_UI})
target_compile_definitions(${TARGET_QT_CLOUD_BASE}_vm PRIVATE USE_VL_MACRO)
target_link_libraries(${TARGET_QT_CLOUD_BASE}_vm PRIVATE Qt6::Widgets libcurl vxlib64)
set_target_properties(${TARGET_QT_CLOUD_BASE}_vm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BASE_DIR_QT}"
    OUTPUT_NAME "${TARGET_QT_CLOUD_BASE}_vm"
    MACOSX_BUNDLE OFF # Set MACOSX_BUNDLE as a property
)
