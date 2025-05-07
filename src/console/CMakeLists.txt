set(TARGET_NAME "console")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_NAME}")

include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/deps
)

add_executable(${TARGET_NAME})
add_executable(${TARGET_NAME}_cloud)

target_compile_definitions(${TARGET_NAME} PRIVATE
  "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

target_compile_definitions(${TARGET_NAME}_cloud PRIVATE
  "SOURCE_ROOT=${CMAKE_SOURCE_DIR}"
)

target_sources(${TARGET_NAME} PRIVATE
        console.cpp
        ${CMAKE_SOURCE_DIR}/public/resources/app.rc
)

target_sources(${TARGET_NAME}_cloud PRIVATE
        console_cloud.cpp
        ${CMAKE_SOURCE_DIR}/public/resources/app.rc
)

target_link_libraries(${TARGET_NAME} PRIVATE 
    vxlib64
)

target_link_libraries(${TARGET_NAME}_cloud PRIVATE 
    vxlib64
    libcurl
)

if(USE_VL_MACRO)
  set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_NAME}_vm"
  )

  set_target_properties(${TARGET_NAME}_cloud PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_NAME}_cloud_vm"
  )
else()
  set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_NAME}"
  )

  set_target_properties(${TARGET_NAME}_cloud PROPERTIES
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_NAME}_cloud"
)
endif()
