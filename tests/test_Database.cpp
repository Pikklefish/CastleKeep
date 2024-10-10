#include <gtest/gtest.h>
#include "database.hpp"
#include "account.hpp"

// Test fixture for setting up and tearing down database connections
class DatabaseTest : public ::testing::Test {
protected:
    Database* db;

    void SetUp() override {
        std::string conninfo = "host=localhost port=5432 dbname=castle user=postgres password=postgresql!";
        db = new Database(conninfo);
        // db->DeleteAccount(123456789);   // Adjust for account ID
        // db->DeleteTransaction(1111111); // Adjust for transaction ID
    }

    void TearDown() override {
        delete db;
    }
};

// Test case for adding an account to the database
TEST_F(DatabaseTest, AddAccountTest) {
    int accountID = 123456789;
    std::string name = "AddAccount_Test";
    double balance = 1000.00;
    std::string password = "securepassword";

    db->AddAccount(accountID, name, balance, password);

    Account retrievedAccount = db->GetAccount(accountID);
    EXPECT_EQ(retrievedAccount.GetAccountID(), accountID);
    EXPECT_EQ(retrievedAccount.GetBalance(), balance);
}

// Test case for updating account balance
TEST_F(DatabaseTest, UpdateBalanceTest) {
    // Assume an account is already created
    int accountID = 23456789;
    std::string name = "UpdateBalance_Test";
    double initialBalance = 1000.00;
    std::string password = "securepassword";

    // Add the account first
    db->AddAccount(accountID, name, initialBalance, password);

    // Now update the balance
    double newBalance = 500.00;
    db->UpdateBalance(accountID, newBalance);

    // Verify the balance was updated by retrieving the account from the database
    Account retrievedAccount = db->GetAccount(accountID);  // GetAccount should return an Account object
    EXPECT_EQ(retrievedAccount.GetBalance(), newBalance);
}

// Test case for saving a transaction
TEST_F(DatabaseTest, SaveTransactionTest) {
    // Transaction data (assuming encryption is handled)
    int transactionID = 1111111;
    std::string status = "success";
    std::string sender = "sender";
    std::string receiver = "receiver";
    std::string amount = "500.00";
    std::string time = "2024-10-07 12:00:00";

    // Save the transaction
    db->SaveTransaction(transactionID, status, sender, receiver, amount, time);

    // Verify the transaction was saved by retrieving it
    std::string transaction = db->GetTransaction(transactionID);
    EXPECT_NE(transaction, "");  // Check that we retrieved a valid transaction
}
