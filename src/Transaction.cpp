#include <iostream>
#include <random>
using namespace std;

#include "transaction.hpp"
#include "account.hpp"
#include "auditLog.hpp"
#include "security.hpp"

int GenerateTransactionID()
{
    random_device rd;                                   // Non-deterministic random number generator
    mt19937 gen(rd());                                  // Seed the generator with a random device
    uniform_int_distribution<> distr(1000000, 9999999); // Range for random ID (7-digit number)
    return distr(gen);
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
    if (ValidateTransaction(sender, receiver, amount))
    {
        sender.Withdraw(amount);
        receiver.Deposit(amount);

        timestamp = std::chrono::system_clock::now();
        int transaction_id = GenerateTransactionID();

        LogTransaction(transaction_id, sender.GetAccountID(), receiver.GetAccountID(), amount, timestamp);
        std::cout << "Transaction Complete of amount: " << amount << std::endl;
    }
    else
    {
        std::cerr << "Transaction processing failed." << std::endl;
    }
}

#include <iomanip>
#include <sstream>

void Transaction::LogTransaction(int transaction_id, int sender_account_id, int receiver_account_id, double amount, const std::chrono::system_clock::time_point &timestamp)
{
    // Convert time_point to a readable string
    std::time_t log_time = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream time_stream;
    time_stream << std::put_time(std::localtime(&log_time), "%Y-%m-%d %H:%M:%S");

    // Prepare transaction details as a single string for encryption
    std::string transaction_data = "Transaction ID: " + std::to_string(transaction_id) +
                                   "\nSender Account ID: " + std::to_string(sender_account_id) +
                                   "\nReceiver Account ID: " + std::to_string(receiver_account_id) +
                                   "\nAmount: " + std::to_string(amount) +
                                   "\nTimestamp: " + time_stream.str();

    // Encrypt the transaction data
    std::string encrypted_data = Security::Encrypt(transaction_data);

    // Log the encrypted transaction details
    AuditLog::Log(transaction_id, encrypted_data);
    std::cout << "Transaction logged successfully (encrypted)!" << std::endl;
}
