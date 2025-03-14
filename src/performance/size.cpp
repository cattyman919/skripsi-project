#include <filesystem> // Include this header
#include <iostream>
#include <windows.h>

#include "vxlang/vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  VL_VIRTUALIZATION_BEGIN;
  std::cout << "Dummy executable with custom size\n";
  fs::path exe_path =
      fs::canonical(fs::path(argv[0])); // Requires including <windows.h>

  // Get the file size
  uintmax_t size = fs::file_size(exe_path);
  std::cout << "Executable size: " << size << " bytes ("
            << (size / 1024.0 / 1024.0) << " MB)\n";
  VL_VIRTUALIZATION_END;
  return 0;
}
