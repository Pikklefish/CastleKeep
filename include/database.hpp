#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <string>

class Database {
public:
    // Constructor to initialize database connection
    Database();

    // Method to add a new account to the database
    void AddAccount(int accountID, const std::string& name, double balance, const std::string& password);

    // Method to update the account balance after a transaction
    void UpdateBalance(int accountID, double new_balance);

private:
    sql::mysql::MySQL_Driver *driver;
    std::unique_ptr<sql::Connection> con;
};

#endif
