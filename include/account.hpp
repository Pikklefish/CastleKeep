#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

class Account
{

private:
    int accountID;
    std::string accountHolderName;
    double balance;
    std::string passwordHash;

public:
    Account(std::string name, double initBalance, std::string hash); // constructor

    // methods
    double getBalance() const; // const ensures nothing is changed
    void deposit(double amount);
    void withdraw(double amount);
    void createAccount(std::string name, std::string password);
    bool authenticatePassword(const std::string& password) const;
};

#endif