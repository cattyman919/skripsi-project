#pragma once

#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

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

      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      curl_slist_free_all(headers);

      // Parse response using JSON library
      json response = json::parse(readBuffer);
      return response.value("success", false);
    }
  } catch (const json::exception &e) {
    std::cerr << "JSON error: " << e.what() << std::endl;
  }
  return false;
}
