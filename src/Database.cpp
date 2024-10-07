#include "database.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <libpq-fe.h>

// Constructor: Initializes the PostgreSQL connection
Database::Database(const std::string& conninfo) {
    conn = PQconnectdb(conninfo.c_str());

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        throw std::runtime_error("Database connection failed.");
    }
}

// Destructor: Closes the PostgreSQL connection
Database::~Database() {
    PQfinish(conn);
}

// Add an account to the accounts table
void Database::AddAccount(int accountID, const std::string& name, double balance, const std::string& password) {
    const char* query = "INSERT INTO accounts (uuid, name, balance, password) VALUES ($1, $2, $3, $4)";
    
    const char* paramValues[4];
    char accountIDStr[12];
    snprintf(accountIDStr, sizeof(accountIDStr), "%d", accountID);
    paramValues[0] = accountIDStr;  // UUID
    paramValues[1] = name.c_str();  // Name
    char balanceStr[32];
    snprintf(balanceStr, sizeof(balanceStr), "%.2f", balance);
    paramValues[2] = balanceStr;    // Balance
    paramValues[3] = password.c_str();  // Password (hashed)

    PGresult* res = PQexecParams(conn, query, 4, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert into accounts failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Account added successfully!" << std::endl;
    }

    PQclear(res);
}

// Update the account balance
void Database::UpdateBalance(int accountID, double new_balance) {
    const char* query = "UPDATE accounts SET balance = $1 WHERE uuid = $2";
    
    const char* paramValues[2];
    char balanceStr[32];
    snprintf(balanceStr, sizeof(balanceStr), "%.2f", new_balance);
    paramValues[0] = balanceStr;    // New balance
    char accountIDStr[12];
    snprintf(accountIDStr, sizeof(accountIDStr), "%d", accountID);
    paramValues[1] = accountIDStr;  // UUID

    PGresult* res = PQexecParams(conn, query, 2, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Update balance failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Balance updated successfully!" << std::endl;
    }

    PQclear(res);
}

// Save a transaction to the logs table (with encryption)
void Database::SaveTransaction(int transaction_id, std::string encrypted_transaction_status, std::string encrypted_transaction_sender, 
                               std::string encrypted_transaction_receiver, std::string encrypted_transaction_amount, std::string encrypted_transaction_time) {
    
    const char* query = "INSERT INTO logs (transaction_id, status, sender, receiver, amount, time) VALUES ($1, $2, $3, $4, $5, $6)";
    
    const char* paramValues[6];
    char transactionIDStr[12];
    snprintf(transactionIDStr, sizeof(transactionIDStr), "%d", transaction_id);
    paramValues[0] = transactionIDStr;  // Transaction ID
    paramValues[1] = encrypted_transaction_status.c_str();  // Encrypted Status
    paramValues[2] = encrypted_transaction_sender.c_str();  // Encrypted Sender
    paramValues[3] = encrypted_transaction_receiver.c_str();  // Encrypted Receiver
    paramValues[4] = encrypted_transaction_amount.c_str();  // Encrypted Amount
    paramValues[5] = encrypted_transaction_time.c_str();  // Encrypted Time

    PGresult* res = PQexecParams(conn, query, 6, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert into logs failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Transaction logged successfully!" << std::endl;
    }

    PQclear(res);
}

// Retrieve a transaction by its ID (for example)
std::string Database::GetTransaction(int transaction_id) {
    const char* query = "SELECT * FROM logs WHERE transaction_id = $1";

    const char* paramValues[1];
    char transactionIDStr[12];
    snprintf(transactionIDStr, sizeof(transactionIDStr), "%d", transaction_id);
    paramValues[0] = transactionIDStr;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Select from logs failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return "";
    }

    std::stringstream resultStream;
    for (int i = 0; i < PQnfields(res); i++) {
        resultStream << PQfname(res, i) << ": " << PQgetvalue(res, 0, i) << std::endl;
    }

    PQclear(res);
    return resultStream.str();
}
