#pragma once

#include <iostream>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>

// Forward declaration for OpenSSL types to avoid including full headers if not
// strictly necessary in the header
struct evp_cipher_st;
typedef struct evp_cipher_st EVP_CIPHER;

class AESCipher {
private:
  const EVP_CIPHER *cipher;
  std::vector<unsigned char> key;
  std::vector<unsigned char> iv;

public:
  // Constructor for AES-CBC-256
  AESCipher();

  // Generate a random key and IV
  bool generateKeyAndIV();

  // Set key and IV manually
  void setKey(const std::vector<unsigned char> &newKey);
  void setIV(const std::vector<unsigned char> &newIV);

  // Get the current key and IV
  const std::vector<unsigned char> &getKey() const;
  const std::vector<unsigned char> &getIV() const;

  // Encrypt data
  std::vector<unsigned char>
  encrypt(const std::vector<unsigned char> &plaintext);

  // Decrypt data
  std::vector<unsigned char>
  decrypt(const std::vector<unsigned char> &ciphertext);
};
