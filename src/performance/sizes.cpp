#include <iostream>

#include "vxlang/vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

// Create a new section for our padding
__attribute__((section(".padding")))
// Creating approximately 10MB of data (10 * 1024 * 1024 bytes)
static unsigned char padding[10 * 1024 * 1024] = {1};

int main() {
  VL_VIRTUALIZATION_BEGIN;
  // Access the padding to prevent it from being optimized out
  volatile unsigned char dummy = padding[0];
  std::cout << "This is a ~10MB executable program\n";
  VL_VIRTUALIZATION_END;
  return 0;
}
