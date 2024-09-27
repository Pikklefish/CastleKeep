#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

class Account
{

private:
    int account_id;
    std::string account_holder_name;
    double balance;
    std::string password_hash;

public:
    Account(std::string name, double init_balance, std::string hash); // constructor

    // methods
    double GetBalance() const; // const ensures nothing is changed
    void Deposit(double amount);
    void Withdraw(double amount);
    bool AuthenticatePassword(const std::string& password) const;
};

#endif