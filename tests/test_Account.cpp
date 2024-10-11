#include <gtest/gtest.h>

#include "account.hpp"
#include "security.hpp"

// Test fixture for account related tests
class AccountTestFixture : public testing::Test
{
protected:
    std::string password;
    Account account;

    AccountTestFixture()
        : password("securepassword123!"),
          account("Account_Test", 100.00, password){}
};

// Test case for initial balance check functionality
TEST_F(AccountTestFixture, Initial_Balance_Test)
{
    EXPECT_EQ(account.GetBalance(), 100.00) << "Initial balance expected 100.00"; // extra information displayed when test failed
}

// Test case for deposit functionality
TEST_F(AccountTestFixture, Deposit_Test)
{
    account.Deposit(23.01);
    EXPECT_EQ(account.GetBalance(), 123.01) << "Balance after deposit expected 123.01";
}

// Test case for withdraw functionality
TEST_F(AccountTestFixture, Withdraw_Test)
{
    account.Withdraw(51.02);
    EXPECT_DOUBLE_EQ(account.GetBalance(), 48.98) << "Balance after withdrawal expected 48.98";
}

// Test case for password authentication
TEST_F(AccountTestFixture, Authenticate_Password_Test)
{
    EXPECT_TRUE(account.AuthenticatePassword(password)) << "Password authentication should pass for correct password";
    EXPECT_FALSE(account.AuthenticatePassword("wrongpassword")) << "Password authentication should fail for incorrect password";
}
