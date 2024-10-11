#include <gtest/gtest.h>

#include "security.hpp"


TEST(SecurityTest, Encryption_Test){
    std::string original_transaction = "Sender: Alice, Receiver: Bob, Amount: 100";

    std::string encrypted_transaction = Security::Encrypt(original_transaction);

    ASSERT_FALSE(encrypted_transaction.empty()) << "Non empty encrypted string expected";
    ASSERT_NE(encrypted_transaction, original_transaction) << "Encrypted string matches original string, non matching string expected";

}

TEST(SecuityTest, Decryption_Test){
    std::string original_transaction = "Sender: Alice, Receiver: Bob, Amount: 100";

    std::string encrypted_transaction = Security::Encrypt(original_transaction);

    std::string decrypted_transaction = Security::Decrypt(encrypted_transaction);

    ASSERT_EQ(decrypted_transaction, original_transaction) << "Decrypted string matching original string expected";
}


TEST(SecurityTest, Password_Hash_Test){
    std::string password = "mySecurePassword123";
    EXPECT_EQ(Security::HashPassword(password), "ca6ee54120465533d367b4cac5cd2f12ee75234225130dd89470de546ab9ca46");

}
