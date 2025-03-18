#include "cloud.hpp"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <windows.h>

#include "vxlang/vxlib.h"
#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif
#pragma comment(lib, "libcurl.lib")

int main() {
  VL_VIRTUALIZATION_BEGIN;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  std::string username, password;
  std::cout << "Enter username: ";
  std::cin >> username;
  std::cout << "Enter password: ";
  std::cin >> password;

  if (send_login_request(username, password)) {
    std::cout << "Authorized!" << std::endl;
  } else {
    std::cout << "Not authorized" << std::endl;
  }

  curl_global_cleanup();
  VL_VIRTUALIZATION_END;

  system("pause");
  return 0;
}
