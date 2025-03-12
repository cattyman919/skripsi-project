#include "EagleVMStub/EagleVMStub.h"
#include <cstdio>
#include <intrin.h>
#include <iostream>
#include <string>

int main(int, char *[]) {
  fnEagleVMBegin();

  std::string correctPassword = "password123";
  std::string inputPassword;

  std::cout << "Enter password: ";
  std::cin >> inputPassword;

  if (inputPassword.compare(correctPassword) == 0) {
    std::cout << "Authorized!" << std::endl;
  } else {
    std::cout << "Not authorized." << std::endl;
  }
  system("pause");

  fnEagleVMEnd();
  return 0;
}

