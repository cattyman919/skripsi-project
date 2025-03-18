#pragma once

#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <windows.h> // Required for MessageBoxW

using json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

bool send_login_request(const std::string &username,
                        const std::string &password, HWND window = NULL) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  std::string url = "http://localhost:9090/login";

  try {
    json payload;
    payload["username"] = username;
    payload["password"] = password;

    std::string jsonStr = payload.dump();

    curl = curl_easy_init();
    if (curl) {
      struct curl_slist *headers = nullptr;
      headers = curl_slist_append(headers, "Content-Type: application/json");

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // 5-second timeout

      res = curl_easy_perform(curl);

      // Always cleanup first
      curl_easy_cleanup(curl);
      curl_slist_free_all(headers);

      // Check for CURL errors
      if (res != CURLE_OK) {
        std::string errorMsg = "Server connection failed (" +
                               std::string(curl_easy_strerror(res)) + ")";

        // Convert to wide string for MessageBoxW
        wchar_t wideMsg[256];
        MultiByteToWideChar(CP_UTF8, 0, errorMsg.c_str(), -1, wideMsg, 256);

        MessageBoxW(NULL, wideMsg, L"Server Connection Error",
                    MB_ICONERROR | MB_OK);
        return false;
      }

      // Check for empty response
      if (readBuffer.empty()) {
        MessageBoxW(NULL, L"Received empty response from server",
                    L"Server Error", MB_ICONERROR | MB_OK);
        return false;
      }

      // Parse response
      json response = json::parse(readBuffer);
      return response.value("success", false);
    }
  } catch (const json::exception &e) {
    MessageBoxW(NULL, L"Invalid response format from server",
                L"Server Communication Error", MB_ICONERROR | MB_OK);
  } catch (...) {
    MessageBoxW(NULL, L"Unknown error occurred during communication",
                L"Network Error", MB_ICONERROR | MB_OK);
  }
  return false;
}
