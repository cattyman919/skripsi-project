#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "vxlang/vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

int main(int, char *[]) {

  VL_VIRTUALIZATION_BEGIN;

  std::string inputUsername;
  std::string inputPassword;

  std::cout << "Enter username: ";
  std::cin >> inputUsername;

  std::cout << "Enter password: ";
  std::cin >> inputPassword;

  if (inputUsername.compare("seno") == 0 &&
      inputPassword.compare("rahman") == 0) {
    std::cout << "Authorized!" << std::endl;
  } else {
    std::cout << "Not authorized." << std::endl;
  }

  VL_VIRTUALIZATION_END;

  system("pause");

  return 0;
}
