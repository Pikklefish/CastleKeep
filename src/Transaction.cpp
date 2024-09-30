#include <iostream>
#include <random>
using namespace std;

#include "transaction.hpp"
#include "account.hpp"
#include "auditLog.hpp"

int GenerateUUID()
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
        int transaction_id = GenerateUUID();

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

void Transaction::LogTransaction(int transaction_id, int sender_account_id, int receiver_account_id, double amount, const std::chrono::system_clock::time_point &timestamp) {
    // Convert time_point to a readable string
    std::time_t log_time = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream time_stream;
    time_stream << std::put_time(std::localtime(&log_time), "%Y-%m-%d %H:%M:%S");

    // Log transaction details (Assuming AuditLog has a method like Log)
    AuditLog::Log(transaction_id, sender_account_id, receiver_account_id, amount, time_stream.str());
    std::cout << "Transaction logged successfully!" << std::endl;
}
