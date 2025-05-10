set(TARGET_QUICKSORT quick_sort)
set(TARGET_ENCRYPTION encryption)
set(TARGET_SIZE size)

########### Target: Quick_Sort ##############

add_executable(${TARGET_QUICKSORT})

target_sources(${TARGET_QUICKSORT} PRIVATE
    quick_sort.cpp
    ${CMAKE_SOURCE_DIR}/public/resources/array.rc
)

target_link_libraries(${TARGET_QUICKSORT} PRIVATE
    vxlib64
)

if(USE_VL_MACRO)
  set_target_properties(${TARGET_QUICKSORT} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_QUICKSORT}/${CMAKE_BUILD_TYPE}"
      CXX_EXTENSIONS OFF
      OUTPUT_NAME "${TARGET_QUICKSORT}_vm"
  )
else()
  set_target_properties(${TARGET_QUICKSORT} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_QUICKSORT}/${CMAKE_BUILD_TYPE}"
      CXX_EXTENSIONS OFF
      OUTPUT_NAME "${TARGET_QUICKSORT}"
  )
endif()

########### Target: Encryption ##############

add_executable(${TARGET_ENCRYPTION})

target_sources(${TARGET_ENCRYPTION} PRIVATE
    encryption.cpp
    aes.cpp
    ${CMAKE_SOURCE_DIR}/public/resources/encrypt.rc
)

target_include_directories(${TARGET_ENCRYPTION} PRIVATE
        ${CMAKE_SOURCE_DIR}/deps
)

target_link_libraries(${TARGET_ENCRYPTION} PRIVATE
    libssl
    libcrypto
    vxlib64
)

if(USE_VL_MACRO)
  set_target_properties(${TARGET_ENCRYPTION} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_ENCRYPTION}/${CMAKE_BUILD_TYPE}"
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_ENCRYPTION}_vm"
)
else()
  set_target_properties(${TARGET_ENCRYPTION} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_ENCRYPTION}/${CMAKE_BUILD_TYPE}"
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_ENCRYPTION}"
)
endif()

########### Target: Size ##############

add_executable(${TARGET_SIZE})

target_sources(${TARGET_SIZE} PRIVATE
    size.cpp
    dummy.rc
    ${CMAKE_SOURCE_DIR}/public/resources/size.rc
)

target_link_libraries(${TARGET_SIZE} PRIVATE
    vxlib64
)

if(USE_VL_MACRO)
  set_target_properties(${TARGET_SIZE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_SIZE}/${CMAKE_BUILD_TYPE}"
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_SIZE}_vm"
)
else()
  set_target_properties(${TARGET_SIZE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${TARGET_SIZE}/${CMAKE_BUILD_TYPE}"
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "${TARGET_SIZE}"
)
endif()
