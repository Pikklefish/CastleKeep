#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <chrono>

class Account;

class Transaction
{

private:
    int transaction_id;
    int sender_account_id;
    int receiver_account_id;
    double amount;
    std::chrono::system_clock::time_point timestamp;
    std::string status;

    std::string sender_account_id_str;
    std::string receiver_account_id_str;
    std::string amount_str;
    std::string timestamp_str;

public:
    Transaction();                                                                                                                                                                  // For creating new transaction
    Transaction(int transaction_id, std::string status, std::string sender_account_id_str, std::string receiver_account_id_str, std::string amount_str, std::string timestamp_str); // For retreiving transaction

    bool ValidateTransaction(Account &sender, Account &receiver, double amount);
    void ProcessTransaction(Account &sender, Account &receiver, double amount);
    void EncryptTransaction(int transaction_id, std::string status, int sender_account_id, int receiver_account_id, double amount, const std::chrono::system_clock::time_point &timestamp);

    int GetTransactionID() const;
    std::string GetAmountSTR() const;
    std::string GetSenderIdSTR() const;
    std::string GetReceiverIdSTR() const;
};
#endif