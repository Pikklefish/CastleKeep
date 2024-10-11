#include <gtest/gtest.h>
#include "database.hpp"
#include "account.hpp"
#include "transaction.hpp"

// Test fixture for setting up and tearing down database connections
class DatabaseTest : public ::testing::Test {
protected:
    Database* db;

    void SetUp() override {
        std::string conninfo = "host=localhost port=5432 dbname=castle user=postgres password=postgresql!";
        db = new Database(conninfo);
        db->DeleteAccount(123456789);   // Adjust for account ID
        db->DeleteAccount(23456789);
        db->DeleteTransaction(1111111); // Adjust for transaction ID
    }

    void TearDown() override {
        delete db;
    }
};

// Test case for adding an account to the database
TEST_F(DatabaseTest, Add_Account_Test) {
    int account_id = 123456789;
    std::string name = "AddAccount_Test";
    double balance = 1000.00;
    std::string password = "securepassword";

    db->AddAccount(account_id, name, balance, password);

    Account retrievedAccount = db->GetAccount(account_id);
    ASSERT_EQ(retrievedAccount.GetAccountID(), account_id);
    EXPECT_EQ(retrievedAccount.GetBalance(), balance);
}

// Test case for updating account balance
TEST_F(DatabaseTest, Update_Balance_Test) {
    // Assume an account is already created
    int account_id = 23456789;
    std::string name = "UpdateBalance_Test";
    double initial_balance = 1000.00;
    std::string password = "securepassword";

    // Add the account first
    db->AddAccount(account_id, name, initial_balance, password);

    // Now update the balance
    double new_balance = 500.00;
    db->UpdateBalance(account_id, new_balance);

    // Verify the balance was updated by retrieving the account from the database
    Account retrievedAccount = db->GetAccount(account_id);  // GetAccount should return an Account object
    ASSERT_EQ(retrievedAccount.GetAccountID(), account_id);
    EXPECT_EQ(retrievedAccount.GetBalance(), new_balance);
}

// Test case for saving a transaction
TEST_F(DatabaseTest, Save_Transaction_Test) {
    // Transaction data (assuming encryption is handled)
    int transaction_id = 1111111;
    std::string status = "success";
    std::string sender = "123435678";
    std::string receiver = "23456789";
    std::string amount = "500.00";
    std::string time = "2024-10-07 12:00:00";

    // Save the transaction
    db->SaveTransaction(transaction_id, status, sender, receiver, amount, time);

    // Verify the transaction was saved by retrieving it
    Transaction retrieved_transaction = db->GetTransaction(transaction_id);
    ASSERT_EQ(retrieved_transaction.GetTransactionID(), transaction_id);
    EXPECT_EQ(retrieved_transaction.GetSenderIdSTR(), sender);
    EXPECT_EQ(retrieved_transaction.GetReceiverIdSTR(), receiver);
    EXPECT_EQ(retrieved_transaction.GetAmountSTR(), amount);
}
