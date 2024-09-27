#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <string>

class Security
{
private:
    static std::string encryption_key;

public:
    static std::string HashPassword(const std::string &password);
    // using AES
    static std::string Encrypt(const std::string &data);

    static std::string Decrypt(const std::string &encrypted_data);
};

#endif