#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <libpq-fe.h>

#include "database.hpp"
#include "account.hpp"


// <<Constructor: Initializes the PostgreSQL connection>>
Database::Database(const std::string& conninfo) {
    conn = PQconnectdb(conninfo.c_str());  //establishes a connection

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        throw std::runtime_error("Database connection failed.");
    }
}

// <<Destructor: Closes the PostgreSQL connection>>
Database::~Database() {
    PQfinish(conn);
}

// <<Add an account to the accounts table>>

void Database::AddAccount(int account_id, const std::string& name, double balance, const std::string& password) {
    const char* query = "INSERT INTO accounts (uuid, name, balance, password) VALUES ($1, $2, $3, $4)";
    
    // Convert account_id to string
    char accountIDStr[12];
    snprintf(accountIDStr, sizeof(accountIDStr), "%d", account_id);
    
    // Convert balance to string
    std::ostringstream balanceStream;
    balanceStream << std::fixed << std::setprecision(2) << balance;
    std::string balanceStr = balanceStream.str();

    // Setup parameters
    const char* paramValues[4];
    paramValues[0] = accountIDStr;        // UUID as a string
    paramValues[1] = name.c_str();        // Name
    paramValues[2] = balanceStr.c_str();  // Balance as a string
    paramValues[3] = password.c_str();    // Password

    // Specify the formats for each parameter
    const int paramFormats[] = {0, 0, 0, 0};  // All parameters as text (0 for text)
    
    // Execute the query
    PGresult* res = PQexecParams(conn, query, 4, NULL, paramValues, NULL, paramFormats, 0);

    // Check result
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert into accounts failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Account added successfully! ID: " << account_id << std::endl;
    }

    PQclear(res);
}



// <<Delete an Account>> 
void Database::DeleteAccount(int account_id){
    const char* query = "DELETE FROM accounts WHERE uuid = $1";

    const char* paramValues[1];
    char accountIDStr[12];
    snprintf(accountIDStr, sizeof(accountIDStr), "%d", account_id);
    paramValues[0] = accountIDStr;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Delete account failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Account deleted successfully! ID: " << account_id << std::endl;
    }

    PQclear(res);
}

// <<Retrieve an Account>>
Account Database::GetAccount(int account_id) {
    const char* query = "SELECT name, balance::double precision, password FROM accounts WHERE uuid = $1";

    char accountIDStr[12];
    snprintf(accountIDStr, sizeof(accountIDStr), "%d", account_id);

    const char* paramValues[1];
    paramValues[0] = accountIDStr;  // Set the account_id as a string

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        throw std::runtime_error("Failed to retrieve account.");
    }

    std::string name = PQgetvalue(res, 0, 0);
    std::string balanceStr = PQgetvalue(res, 0, 1);  // Balance as string
    std::string passwordHash = PQgetvalue(res, 0, 2);

    // Safely handle the conversion of balance from string to double
    double balance;
    try {
        balance = std::stod(balanceStr);  // Convert the balance from string to double
    } catch (const std::invalid_argument& e) {
        PQclear(res);
        throw std::runtime_error("Invalid balance format in the database.");
    }

    PQclear(res);

    return Account(*this, account_id, name, balance, passwordHash);
}


// <<Update the account balance>>
void Database::UpdateBalance(int account_id, double new_balance) {
    const char* query = "UPDATE accounts SET balance = $1 WHERE uuid = $2";
    
    char accountIDStr[12];
    snprintf(accountIDStr, sizeof(accountIDStr), "%d", account_id);
    
    // Convert balance to string
    std::ostringstream balanceStream;
    balanceStream << std::fixed << std::setprecision(2) << new_balance;
    std::string balanceStr = balanceStream.str();

    // Setup parameters
    const char* paramValues[4];
    paramValues[0] = balanceStr.c_str();        // UUID as a string
    paramValues[1] = accountIDStr;  // Balance as a string

    // Specify the formats for each parameter
    const int paramFormats[] = {0, 0};  // All parameters as text (0 for text)
    
    // Execute the query
    PGresult* res = PQexecParams(conn, query, 2, NULL, paramValues, NULL, paramFormats, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Update balance failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Balance updated successfully! ID: " << account_id << std::endl;
    }

    PQclear(res);
}


// <<Save a transaction to the logs table (with encryption)>>
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
        std::cout << "Transaction logged successfully! ID: " << transaction_id << std::endl;
    }

    PQclear(res);
}

// <<Delete transaction>> 
void Database::DeleteTransaction(int transaction_id){
    const char* query = "DELETE FROM logs WHERE transaction_id = $1";
    const char* paramValues[1];
    char transactionIDStr[12];
    snprintf(transactionIDStr, sizeof(transactionIDStr), "%d", transaction_id);
    paramValues[0] = transactionIDStr;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Delete transaction failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Transaction deleted successfully! ID: " << transaction_id << std::endl;
    }

    PQclear(res);
}


// <<Retrieve a transaction by its ID (for example)>>
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
