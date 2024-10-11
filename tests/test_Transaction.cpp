#include <gtest/gtest.h>

#include "account.hpp"
#include "transaction.hpp"

// Validate transaction with a sufficient balance
TEST(TransactionTest, ValidateTransactionSuccess) {
    Account sender( "V_trans_success_sender", 5000.0, "hashed_password");
    Account receiver("V_trans_success_receiver", 1000.0, "hashed_password");
    Transaction transaction;

    // Validate transaction with a sufficient balance
    ASSERT_TRUE(transaction.ValidateTransaction(sender, receiver, 2000.0));
}

// Validate transaction with an insufficient balance
TEST(TransactionTest, ValidateTransactionFail) {
    Account sender("V_trans_fail_sender", 500.0, "hashed_password");
    Account receiver("V_trans_fail_receiver", 1000.0, "hashed_password");
    Transaction transaction;

    ASSERT_FALSE(transaction.ValidateTransaction(sender, receiver, 2000.0));
}

// Process a successful transaction
TEST(TransactionTest, ProcessTransactionSuccess) {
    Account sender("P_trans_success_sender", 5000.0, "hashed_password");
    Account receiver("P_trans_success_receiver", 1000.0, "hashed_password");
    Transaction transaction;

    transaction.ProcessTransaction(sender, receiver, 2000.0);

    // Verify balances after the transaction
    EXPECT_EQ(sender.GetBalance(), 3000.0);  // Sender's balance should decrease
    EXPECT_EQ(receiver.GetBalance(), 3000.0);  // Receiver's balance should increase
}

// Attempt to process a transaction with insufficient funds
TEST(TransactionTest, ProcessTransactionFail) {
    Account sender("P_trans_fail_sender", 500.0, "hashed_password");
    Account receiver("P_trans_fail_receiver", 1000.0, "hashed_password");
    Transaction transaction;

    
    transaction.ProcessTransaction(sender, receiver, 2000.0);

    // Verify that balances remain unchanged
    EXPECT_EQ(sender.GetBalance(), 500.0);
    EXPECT_EQ(receiver.GetBalance(), 1000.0);
}

