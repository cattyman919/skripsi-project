#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define USE_VL_MACRO
#include "vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

int main(int, char *[]) {

  VL_VIRTUALIZATION_BEGIN;

  std::string correctPassword = "password123";
  std::string inputPassword;

  std::cout << "Enter password: ";
  std::cin >> inputPassword;

  if (inputPassword.compare(correctPassword) == 0) {
    std::cout << "Authorized!" << std::endl;
  } else {
    std::cout << "Not authorized." << std::endl;
  }

  VL_VIRTUALIZATION_END;

  system("pause");

  return 0;
}
