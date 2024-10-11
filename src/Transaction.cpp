#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <sstream>
using namespace std;

#include "transaction.hpp"
#include "account.hpp"
#include "security.hpp"

int GenerateTransactionID()
{
    random_device rd;                                   // Non-deterministic random number generator
    mt19937 gen(rd());                                  // Seed the generator with a random device
    uniform_int_distribution<> distr(1000000, 9999999); // Range for random ID (7-digit number)
    return distr(gen);
}

// Constructor for creating transaction
Transaction::Transaction() : transaction_id(GenerateTransactionID())
{
    cout << "Transaction successfully created, ID: " << transaction_id << endl;
}

// constructor for retrieving transaction
Transaction::Transaction(int transaction_id, std::string status, std::string sender_account_id_str, std::string receiver_account_id_str, std::string amount_str, std::string timestamp_str)
    : transaction_id(transaction_id),
      status(status),
      sender_account_id_str(sender_account_id_str),
      receiver_account_id_str(receiver_account_id_str),
      amount_str(amount_str),
      timestamp_str(timestamp_str)
{
    cout << "Transaction successfully retrieved, ID: " << transaction_id << endl;
}

bool Transaction::ValidateTransaction(Account &sender, Account &receiver, double amount)
{
    if (sender.GetBalance() < amount)
    {
        std::cerr << "Transaction failed: Insufficient funds." << std::endl;
        return false;
    }
    return true;
}

void Transaction::ProcessTransaction(Account &sender, Account &receiver, double amount)
{
    timestamp = std::chrono::system_clock::now();

    if (ValidateTransaction(sender, receiver, amount))
    {
        sender.Withdraw(amount);
        receiver.Deposit(amount);
        string status = "success";

        EncryptTransaction(transaction_id, status, sender.GetAccountID(), receiver.GetAccountID(), amount, timestamp);
        std::cout << "Transaction Complete of amount: " << amount << std::endl;
    }
    else
    {
        string status = "fail";
        EncryptTransaction(transaction_id, status, sender.GetAccountID(), receiver.GetAccountID(), amount, timestamp);
        std::cerr << "Transaction processing failed." << std::endl;
    }
}

void Transaction::EncryptTransaction(int transaction_id, string status, int sender_account_id, int receiver_account_id, double amount, const std::chrono::system_clock::time_point &timestamp)
{
    // Convert time_point to a readable string
    std::time_t log_time = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream time_stream;
    time_stream << std::put_time(std::localtime(&log_time), "%Y-%m-%d %H:%M:%S");

    // Prepare transaction details as a single string for encryption
    std::string transaction_status = status;
    std::string transaction_sender = std::to_string(sender_account_id);
    std::string transaction_receiver = std::to_string(receiver_account_id);
    std::string transaction_amount = std::to_string(amount);
    std::string transaction_time = time_stream.str();

    // Encrypt the transaction data
    std::string encrypted_transaction_status = Security::Encrypt(transaction_status);
    std::string encrypted_transaction_sender = Security::Encrypt(transaction_sender);
    std::string encrypted_transaction_receiver = Security::Encrypt(transaction_receiver);
    std::string encrypted_transaction_amount = Security::Encrypt(transaction_amount);
    std::string encrypted_transaction_time = Security::Encrypt(transaction_time);

    std::cout << "Transaction encrypted successfully (encrypted)!" << std::endl;
}

int Transaction::GetTransactionID() const
{
    return transaction_id;
}

std::string Transaction::GetAmountSTR() const
{
    return amount_str;
}

std::string Transaction::GetSenderIdSTR() const
{
    return sender_account_id_str;
}

std::string Transaction::GetReceiverIdSTR() const
{
    return receiver_account_id_str;
}