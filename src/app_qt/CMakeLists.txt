set(TARGET_NAME "app_qt")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_NAME}")
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_SOURCE_DIR}/deps
)

file(GLOB_RECURSE APP_QT_SOURCES_UI
    "forms/*.ui"
)

file(GLOB_RECURSE APP_QT_HEADERS
    "${CMAKE_SOURCE_DIR}/includes/app_qt/*.h"
)

# Define a variable for the source files that are common to both executables
set(COMMON_APP_SOURCES
    src/main.cpp
    src/todo.cpp
    ${APP_QT_HEADERS}
    ${CMAKE_SOURCE_DIR}/public/resources/qt.rc 
)

qt_add_executable(${TARGET_NAME} 
  ${COMMON_APP_SOURCES}
  src/todo_auth.cpp
)


qt_add_executable(${TARGET_NAME}_cloud 
  ${COMMON_APP_SOURCES}
  src/todo_auth_cloud.cpp
)

qt_add_ui(${TARGET_NAME} SOURCES ${APP_QT_SOURCES_UI})
qt_add_ui(${TARGET_NAME}_cloud SOURCES ${APP_QT_SOURCES_UI})

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${TARGET_NAME}_cloud PRIVATE Qt6::Widgets libcurl)

if(USE_VL_MACRO)

  set_target_properties(${TARGET_NAME} PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}_vm"
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
  )

  set_target_properties(${TARGET_NAME}_cloud PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}_cloud_vm"
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
  )

else()
  set_target_properties(${TARGET_NAME} PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}"
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
  )

  set_target_properties(${TARGET_NAME}_cloud PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}_cloud"
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
  )
endif()
