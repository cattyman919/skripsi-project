#include "encryption/aes.h"

// Constructor for AES-CBC-256
AESCipher::AESCipher() : cipher(EVP_aes_256_cbc()) {
  // AES-256 uses a 32-byte key
  key.resize(32);
  // CBC mode requires an IV of the same size as the block size (16 bytes for
  // AES)
  iv.resize(16);
}

// Generate a random key and IV
bool AESCipher::generateKeyAndIV() {
  if (RAND_bytes(key.data(), key.size()) != 1) {
    std::cerr << "Error generating random key\n";
    return false;
  }

  if (RAND_bytes(iv.data(), iv.size()) != 1) {
    std::cerr << "Error generating random IV\n";
    return false;
  }

  return true;
}

// Set key and IV manually
void AESCipher::setKey(const std::vector<unsigned char> &newKey) {
  if (newKey.size() != key.size()) {
    throw std::runtime_error("Invalid key size");
  }
  key = newKey;
}

void AESCipher::setIV(const std::vector<unsigned char> &newIV) {
  if (newIV.size() != iv.size()) {
    throw std::runtime_error("Invalid IV size");
  }
  iv = newIV;
}

// Get the current key and IV
const std::vector<unsigned char> &AESCipher::getKey() const { return key; }
const std::vector<unsigned char> &AESCipher::getIV() const { return iv; }

// Encrypt data
std::vector<unsigned char>
AESCipher::encrypt(const std::vector<unsigned char> &plaintext) {
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    throw std::runtime_error("Failed to create cipher context");
  }

  // Initialize the encryption operation
  if (EVP_EncryptInit_ex(ctx, cipher, nullptr, key.data(), iv.data()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Failed to initialize encryption");
  }

  // Allocate space for the ciphertext
  // The maximum size may be larger than plaintext by up to one block size
  std::vector<unsigned char> ciphertext(plaintext.size() +
                                        EVP_CIPHER_block_size(cipher));
  int len = 0;
  int ciphertext_len = 0;

  // Provide the message to be encrypted, and obtain the encrypted output
  if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(),
                        plaintext.size()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Failed during encryption");
  }
  ciphertext_len = len;

  // Finalize the encryption
  if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Failed to finalize encryption");
  }
  ciphertext_len += len;

  // Clean up
  EVP_CIPHER_CTX_free(ctx);

  // Resize the ciphertext to the actual size
  ciphertext.resize(ciphertext_len);
  return ciphertext;
}

// Decrypt data
std::vector<unsigned char>
AESCipher::decrypt(const std::vector<unsigned char> &ciphertext) {
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    throw std::runtime_error("Failed to create cipher context");
  }

  // Initialize the decryption operation
  if (EVP_DecryptInit_ex(ctx, cipher, nullptr, key.data(), iv.data()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Failed to initialize decryption");
  }

  // Allocate space for the plaintext
  // The maximum size may be larger than ciphertext by up to one block size
  std::vector<unsigned char> plaintext(ciphertext.size() +
                                       EVP_CIPHER_block_size(cipher));
  int len = 0;
  int plaintext_len = 0;

  // Provide the message to be decrypted, and obtain the decrypted output
  if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(),
                        ciphertext.size()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Failed during decryption");
  }
  plaintext_len = len;

  // Finalize the decryption
  if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Failed to finalize decryption");
  }
  plaintext_len += len;

  // Clean up
  EVP_CIPHER_CTX_free(ctx);

  // Resize the plaintext to the actual size
  plaintext.resize(plaintext_len);
  return plaintext;
}
