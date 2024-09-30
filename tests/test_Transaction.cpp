#include <gtest/gtest.h>

#include "account.hpp"
#include "auditLog.hpp"
#include "transaction.hpp"


// Validate transaction with a sufficient balance
TEST(TransactionTest, ValidateTransactionSuccess) {
    Account sender("John Doe", 5000.0, "hashed_password");
    Account receiver("Jane Doe", 1000.0, "hashed_password");
    Transaction transaction;

    // Validate transaction with a sufficient balance
    ASSERT_TRUE(transaction.ValidateTransaction(sender, receiver, 2000.0));
}

// Validate transaction with an insufficient balance
TEST(TransactionTest, ValidateTransactionFail) {
    Account sender("John Doe", 500.0, "hashed_password");
    Account receiver("Jane Doe", 1000.0, "hashed_password");
    Transaction transaction;

    ASSERT_FALSE(transaction.ValidateTransaction(sender, receiver, 2000.0));
}

// Process a successful transaction
TEST(TransactionTest, ProcessTransactionSuccess) {
    Account sender("John Doe", 5000.0, "hashed_password");
    Account receiver("Jane Doe", 1000.0, "hashed_password");
    Transaction transaction;

    transaction.ProcessTransaction(sender, receiver, 2000.0);

    // Verify balances after the transaction
    EXPECT_EQ(sender.GetBalance(), 3000.0);  // Sender's balance should decrease
    EXPECT_EQ(receiver.GetBalance(), 3000.0);  // Receiver's balance should increase
}

// Attempt to process a transaction with insufficient funds
TEST(TransactionTest, ProcessTransactionFail) {
    Account sender("John Doe", 500.0, "hashed_password");
    Account receiver("Jane Doe", 1000.0, "hashed_password");
    Transaction transaction;

    
    transaction.ProcessTransaction(sender, receiver, 2000.0);

    // Verify that balances remain unchanged
    EXPECT_EQ(sender.GetBalance(), 500.0);
    EXPECT_EQ(receiver.GetBalance(), 1000.0);
}


// Process the transaction and log it
TEST(TransactionTest, LogTransactionTest) {
    Account sender("John Doe", 5000.0, "hashed_password");
    Account receiver("Jane Doe", 1000.0, "hashed_password");
    Transaction transaction;    
    transaction.ProcessTransaction(sender, receiver, 1000.0);

    SUCCEED();
}
