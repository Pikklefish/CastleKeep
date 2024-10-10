#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <libpq-fe.h>  // PostgreSQL C API
#include <string>

class Account;
class Transaction;

class Database {
public:
    // Constructor to initialize the database connection
    Database(const std::string& conninfo);

    // Destructor to close the connection
    ~Database();

    // Method to add a new account to the database
    void AddAccount(int account_id, const std::string& name, double balance, const std::string& password);

    // Method to delete account 
    void DeleteAccount(int account_id);

    // Method to update the account balance after a transaction
    void UpdateBalance(int account_id, double new_balance);

    // Method to get account
    Account GetAccount(int account_id);

    // Method to save transaction
    void SaveTransaction(int transaction_id, std::string encrypted_transaction_status, std::string encrypted_transaction_sender, std::string encrypted_transaction_receiver,
                        std::string encrypted_transaction_amount, std::string encrypted_transaction_time);

    // Method to delete transaction
    void DeleteTransaction(int transaction_id);

    // Method to get transaction
    std::string GetTransaction(int transaction_id);

    //we make the methods non static so that they will only function when a db instance exists (db connection is established)
private:
    // PostgreSQL connection handle
    PGconn* conn;
};

#endif
