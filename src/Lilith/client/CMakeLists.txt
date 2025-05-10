file(GLOB_RECURSE SOURCES "*.cpp")

set(TARGET_NAME "Lilith_Client")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_NAME}/${CMAKE_BUILD_TYPE}")

set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(${TARGET_NAME} WIN32 ${SOURCES})

target_link_libraries(${TARGET_NAME} PRIVATE 
    vxlib64
)

if(USE_VL_MACRO)
  set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_NAME}_vm"
  )

else()
  set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_NAME}"
  )

endif()
