#include "security.h"
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

string Security::encryptionKey = "my_secure_123456";

void handleOpenSSLError(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

string Security::encrypt(const string &data){

    unsigned char key[16];
    memcpy(key, Security::encryptionKey.data(), 16);

    // randomly generate initialization vector AES-CBC
    unsigned char iv[16];
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        handleOpenSSLError();
    }

    // Create the encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        handleOpenSSLError();

    // Init the encryption for AES128CBC
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        handleOpenSSLError();
    }

    // providing the data to be encrypted
    unsigned char ciphertext[128];
    int len;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)data.c_str(), data.length()))
    {
        handleOpenSSLError();
    }

    int ciphertext_len = len;

    // finalize the encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        handleOpenSSLError();
    }

    ciphertext_len += len;

    // clean up
    EVP_CIPHER_CTX_free(ctx);

    // Return the IV + ciphertext as the final encrypted message (IV must be sent with the ciphertext)
    return string((char *)iv, 16) + string((char *)ciphertext, ciphertext_len);
}

string Security::decrypt(const string &encryptedData){
    // Extract the IV (first 16 bytes) and the ciphertext
    unsigned char iv[16];
    memcpy(iv, encryptedData.data(), 16);
    string ciphertext = encryptedData.substr(16);

    unsigned char key[16];
    memcpy(key, Security::encryptionKey.data(), 16);

    unsigned char plaintext[128];
    int len;

    // Create the decryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        handleOpenSSLError();

    // Initialize the decryption operation for AES-128-CBC
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        handleOpenSSLError();
    }

    // Provide the data to be decrypted
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char *)ciphertext.c_str(), ciphertext.length()))
    {
        handleOpenSSLError();
    }
    int plaintext_len = len;

    // Finalize the decryption
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    {
        handleOpenSSLError();
    }
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Return the decrypted plaintext as a string
    return string((char *)plaintext, plaintext_len);
}

// Convert unsigned char array to a hex string
string toHexString(const unsigned char *hash, size_t length){
    stringstream ss;
    for (size_t i = 0; i < length; ++i)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Hash the password using SHA-256
string Security::hashPassword(const string &password){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password.c_str(), password.length(), hash);

    // Convert the hash to a readable hex string and return it
    return toHexString(hash, SHA256_DIGEST_LENGTH);
}