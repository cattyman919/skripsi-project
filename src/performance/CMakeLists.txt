set(PERF_OUTPUT_SUBDIR_QS quick_sort)
set(PERF_OUTPUT_SUBDIR_ENC encryption)
set(PERF_OUTPUT_SUBDIR_SIZE size)

# --- Quick Sort ---
add_project_executables(quick_sort
    OUTPUT_SUBDIR ${PERF_OUTPUT_SUBDIR_QS}
    SOURCES quick_sort.cpp
    RC_FILE ${CMAKE_SOURCE_DIR}/public/resources/array.rc
    VM_LIBS vxlib64
)

# --- Encryption ---
include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/deps) # For OpenSSL
add_project_executables(encryption
    OUTPUT_SUBDIR ${PERF_OUTPUT_SUBDIR_ENC}
    SOURCES encryption.cpp aes.cpp
    RC_FILE ${CMAKE_SOURCE_DIR}/public/resources/encrypt.rc
    NON_VM_LIBS libssl libcrypto
    VM_LIBS libssl libcrypto vxlib64
)

# --- Size ---
# This one has a dummy.rc that might be specific.
# If dummy.rc is just data, it's fine.
add_project_executables(size
    OUTPUT_SUBDIR ${PERF_OUTPUT_SUBDIR_SIZE}
    SOURCES size.cpp dummy.rc # Note: dummy.rc included as a source for simplicity
    RC_FILE ${CMAKE_SOURCE_DIR}/public/resources/size.rc
    VM_LIBS vxlib64
)
