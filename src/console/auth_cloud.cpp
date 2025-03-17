#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <string>
#include <vector>
#include <windows.h>

#include "vxlang/vxlib.h"
#include <curl/curl.h>
#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "libcrypto.lib")

// Libcurl write callback
static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// Base64 encoding
std::string base64_encode(const std::vector<unsigned char> &buffer) {
  BIO *bio, *b64;
  BUF_MEM *bufferPtr;

  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
  BIO_write(bio, buffer.data(), static_cast<int>(buffer.size()));
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferPtr);

  std::string result(bufferPtr->data, bufferPtr->length);
  BIO_free_all(bio);

  return result;
}

// Password hashing using PBKDF2-HMAC-SHA256
std::vector<unsigned char>
hash_password(const std::string &password,
              const std::vector<unsigned char> &salt) {
  const int iterations = 100000;
  const int key_length = 32; // SHA-256
  std::vector<unsigned char> hash(key_length);

  PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(),
                    salt.size(), iterations, EVP_sha256(), key_length,
                    hash.data());

  return hash;
}

// Get salt from backend
std::vector<unsigned char> get_salt(const std::string &username) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  std::string url = "http://localhost:8080/salt/" + username;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // Simple JSON parsing (consider using a proper JSON library)
    size_t start = readBuffer.find("\"salt\":\"") + 8;
    size_t end = readBuffer.find("\"", start);
    if (start != std::string::npos && end != std::string::npos) {
      std::string salt_b64 = readBuffer.substr(start, end - start);

      // Base64 decode
      BIO *b64 = BIO_new(BIO_f_base64());
      BIO *mem = BIO_new_mem_buf(salt_b64.c_str(), salt_b64.length());
      BIO_push(b64, mem);

      std::vector<unsigned char> salt(salt_b64.length());
      int salt_len = BIO_read(b64, salt.data(), salt_b64.length());
      salt.resize(salt_len);

      BIO_free_all(b64);
      return salt;
    }
  }
  return {};
}

// Send login request
bool send_login_request(const std::string &username,
                        const std::vector<unsigned char> &hash) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  std::string url = "http://localhost:8080/login";

  std::string hash_b64 = base64_encode(hash);
  std::string json = "{\"username\":\"" + username + "\",\"password_hash\":\"" +
                     hash_b64 + "\"}";

  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    // Check response
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

  // Get salt from backend
  std::vector<unsigned char> salt = get_salt(username);
  if (salt.empty()) {
    std::cout << "Invalid username or error retrieving salt" << std::endl;
    system("pause");
    return 1;
  }

  // Hash password
  std::vector<unsigned char> hash = hash_password(password, salt);

  // Send login request
  if (send_login_request(username, hash)) {
    std::cout << "Authorized!" << std::endl;
  } else {
    std::cout << "Not authorized" << std::endl;
  }

  curl_global_cleanup();
  VL_VIRTUALIZATION_END;
  system("pause");
  return 0;
}
