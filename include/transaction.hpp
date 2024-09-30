#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <chrono>

#include "account.hpp"

class Transaction
{

private:
    int transaction_id;
    int sender_account_id;
    int receiver_account_id;
    std::chrono::system_clock::time_point timestamp;

public:
    bool ValidateTransaction(Account& sender, Account& receiver, double amount);
    void ProcessTransaction(Account& sender, Account& receiver, double amount);
    void LogTransaction(int transaction_id, int sender_account_id, int receiver_account_id, double amount, const std::chrono::system_clock::time_point& timestamp );
};
#endif