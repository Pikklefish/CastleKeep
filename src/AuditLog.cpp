#include "AuditLog.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Path to the log file (modifiable based on your requirements)
const std::string AuditLog::log_file_path = "C:/Users/work/Castle/logs/transaction_log.txt";

void AuditLog::Log(int transaction_id, const std::string &encrypted_data)
{
    std::ofstream log_file(log_file_path, std::ios_base::app); // Open the log file in append mode

    if (log_file.is_open())
    {
        log_file << "Transaction ID: " << transaction_id << "\n"
                 << "Encrypted Data: " << encrypted_data << "\n"
                 << "-----------------------------\n";
        log_file.close();
    }
    else
    {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}
