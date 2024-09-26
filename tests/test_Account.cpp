#include <gtest/gtest.h>

#include "account.hpp"
#include "security.hpp"


// Test case for account creation and initial balance
//this is one test
TEST(AccountTest_1, InitialBalanceTest) {   // ASSERT (abort when failed)  EXPECT (Cont. even if failed)
    std::string password = "securepassword123!";
    Account account_1("Peter Song", 100.00, Security::hashPassword(password));
    EXPECT_EQ(account_1.getBalance(), 100.00) << "Initial balance expected 100.00"; //extra information displayed when test failed
}

// Test case for deposit functionality
TEST(AccountTest_2, DepositTest) {
    std::string password = "securepassword123!";
    Account account_2("Peter Song", 100.00, Security::hashPassword(password));
    account_2.deposit(23.01);
    EXPECT_EQ(account_2.getBalance(), 123.01) << "Balance after deposit expected 123.01";
}

// Test case for withdraw functionality
TEST(AccountTest_3, WithdrawTest) {
    std::string password = "securepassword123!";
    Account account_3("Peter Song", 100.00, Security::hashPassword(password));
    account_3.withdraw(51.02);
    EXPECT_DOUBLE_EQ(account_3.getBalance(), 48.98) << "Balance after withdrawal expected 48.98";
}

// Test case for password authentication
TEST(SecurityTest, AuthenticatePasswordTest) {
    std::string password = "securepassword123!";
    Account account_1("Peter Song", 100.00, Security::hashPassword(password));
    EXPECT_TRUE(account_1.authenticatePassword(password)) << "Password authentication should pass for correct password";
    EXPECT_FALSE(account_1.authenticatePassword("wrongpassword")) << "Password authentication should fail for incorrect password";
}
