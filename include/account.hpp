#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

class Database; //forward declaration tells the header file the class exists but don't need to know the full definition just yet (avoid cricular def)

class Account
{

private:
    int account_id;
    std::string account_holder_name;
    double balance;
    std::string password_hash;
    Database& db;

public:
     // Constructor for creating a new account
    Account(Database& db, std::string name, double init_balance, std::string hash);

    // Constructor for retrieving an existing account
    Account(Database& db, int account_id, std::string name, double init_balance, std::string hash);  //without this whenever the account object is called its constructor will be called generating a new random UUID

    // methods
    double GetBalance() const; // const ensures nothing is changed
    void Deposit(double amount);
    void Withdraw(double amount);
    bool AuthenticatePassword(const std::string& password) const;
    int GetAccountID() const;
};

#endif