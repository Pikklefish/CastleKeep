#include "security.hpp"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
using namespace std;

string Security::encryption_key = "my_secure_123456";

void HandleOpenSSLError(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

string Security::Encrypt(const string &data){

    unsigned char key[16];
    memcpy(key, Security::encryption_key.data(), 16);

    // randomly generate initialization vector AES-CBC
    unsigned char iv[16];
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        HandleOpenSSLError();
    }

    // Create the encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        HandleOpenSSLError();

    // Init the encryption for AES128CBC
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        HandleOpenSSLError();
    }

    // providing the data to be encrypted
    unsigned char ciphertext[128];
    int len;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)data.c_str(), data.length()))
    {
        HandleOpenSSLError();
    }

    int ciphertext_len = len;

    // finalize the encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        HandleOpenSSLError();
    }

    ciphertext_len += len;

    // clean up
    EVP_CIPHER_CTX_free(ctx);

    // Return the IV + ciphertext as the final encrypted message (IV must be sent with the ciphertext)
    return string((char *)iv, 16) + string((char *)ciphertext, ciphertext_len);
}

string Security::Decrypt(const string &encrypted_data){
    // Extract the IV (first 16 bytes) and the ciphertext
    unsigned char iv[16];
    memcpy(iv, encrypted_data.data(), 16);
    string ciphertext = encrypted_data.substr(16);

    unsigned char key[16];
    memcpy(key, Security::encryption_key.data(), 16);

    unsigned char plaintext[128];
    int len;

    // Create the decryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        HandleOpenSSLError();

    // Initialize the decryption operation for AES-128-CBC
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        HandleOpenSSLError();
    }

    // Provide the data to be decrypted
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char *)ciphertext.c_str(), ciphertext.length()))
    {
        HandleOpenSSLError();
    }
    int plaintext_len = len;

    // Finalize the decryption
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    {
        HandleOpenSSLError();
    }
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Return the decrypted plaintext as a string
    return string((char *)plaintext, plaintext_len);
}

// Convert unsigned char array to a hex string
string ToHexString(const unsigned char *hash, size_t length){
    stringstream ss;
    for (size_t i = 0; i < length; ++i)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Hash the password using SHA-256
string Security::HashPassword(const string &password){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password.c_str(), password.length(), hash);

    // Convert the hash to a readable hex string and return it
    return ToHexString(hash, SHA256_DIGEST_LENGTH);
}