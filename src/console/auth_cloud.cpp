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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

bool send_login_request(const std::string &username,
                        const std::string &password) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  std::string url = "http://localhost:8080/login";

  std::string json =
      "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";

  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return readBuffer.find("\"success\":true") != std::string::npos;
  }
  return false;
}

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
