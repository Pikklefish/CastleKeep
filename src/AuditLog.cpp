#include "AuditLog.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Path to the log file (modifiable based on your requirements)
const std::string AuditLog::log_file_path = "C:/Users/work/Castle/logs/transaction_log.txt";

void AuditLog::Log(int transaction_id, int sender_id, int receiver_id, double amount, const std::string& timestamp) {
    // Log transaction details to database or file (example using file)
    std::ofstream log_file("transaction_log.txt", std::ios_base::app); // Open in append mode
    if (log_file.is_open()) {
        log_file << "Transaction ID: " << transaction_id << "\n"
                 << "Sender Account ID: " << sender_id << "\n"
                 << "Receiver Account ID: " << receiver_id << "\n"
                 << "Amount: $" << amount << "\n"
                 << "Timestamp: " << timestamp << "\n"
                 << "-----------------------------\n";
        log_file.close();
    } else {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}


// Helper function to convert time_point to a readable string
std::string AuditLog::FormatTimestamp(const std::chrono::system_clock::time_point& timestamp) {
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S"); // Format as "YYYY-MM-DD HH:MM:SS"
    return ss.str();
}
