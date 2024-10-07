#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <libpq-fe.h>  // PostgreSQL C API
#include <string>

#include "account.hpp"
#include "transaction.hpp"

class Database {
public:
    // Constructor to initialize the database connection
    Database(const std::string& conninfo);

    // Destructor to close the connection
    ~Database();

    // Method to add a new account to the database
    void AddAccount(int accountID, const std::string& name, double balance, const std::string& password);

    // Method to update the account balance after a transaction
    void UpdateBalance(int accountID, double new_balance);

    Account GetAccount(int accountID);

    void SaveTransaction(int transaction_id, std::string encrypted_transaction_status, std::string encrypted_transaction_sender, std::string encrypted_transaction_receiver,
                        std::string encrypted_transaction_amount, std::string encrypted_transaction_time);

    std::string GetTransaction(int transaction_id);

    //we make the methods non static so that they will only function when a db instance exists (db connection is established)
private:
    // PostgreSQL connection handle
    PGconn* conn;
};

#endif
