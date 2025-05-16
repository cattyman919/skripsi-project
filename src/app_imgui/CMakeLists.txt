find_package(OpenGL REQUIRED)

include_directories(PRIVATE
    ${CMAKE_SOURCE_DIR}/deps
    ${CMAKE_SOURCE_DIR}/deps/imgui
    ${CMAKE_SOURCE_DIR}/deps/imgui/backends
)

# Shared ImGui sources (compiled once per executable effectively, or put in a static lib)
file(GLOB_RECURSE VAR_SOURCES_DEPS CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/deps/imgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/deps/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/deps/imgui/backends/imgui_impl_opengl3.cpp"
)
# If you want to ensure ImGui is compiled truly once, make it a static library:
# add_library(imgui_custom STATIC ${VAR_SOURCES_DEPS})
# target_include_directories(imgui_custom PUBLIC
#     ${CMAKE_SOURCE_DIR}/deps/imgui
#     ${CMAKE_SOURCE_DIR}/deps/imgui/backends
# )
# And then link against imgui_custom instead of adding VAR_SOURCES_DEPS to executables.
# For simplicity here, we'll add sources directly. CMake/Ninja will optimize if flags are same.

set(COMMON_APP_IMGUI_SOURCES
    main.cpp
    helper.cpp # Does not use VL_MACRO, can be shared
    ${VAR_SOURCES_DEPS} # ImGui sources
)

set(APP_IMGUI_RC_FILE ${CMAKE_SOURCE_DIR}/public/resources/app.rc)
set(APP_IMGUI_DEFINITIONS "SOURCE_ROOT=${CMAKE_SOURCE_DIR}")

add_project_executables(app_imgui
    IS_GUI_APP
    OUTPUT_SUBDIR app_imgui
    COMMON_SOURCES ${COMMON_APP_IMGUI_SOURCES}
    SOURCES login.cpp # Specific: uses VL_MACRO
    CLOUD_SOURCES login_cloud.cpp # Specific: uses VL_MACRO
    RC_FILE ${APP_IMGUI_RC_FILE}
    DEFINITIONS ${APP_IMGUI_DEFINITIONS}
    NON_VM_LIBS glfw3 OpenGL::GL
    VM_LIBS glfw3 OpenGL::GL vxlib64
    CLOUD_NON_VM_LIBS glfw3 OpenGL::GL libcurl
    CLOUD_VM_LIBS glfw3 OpenGL::GL vxlib64 libcurl
)
