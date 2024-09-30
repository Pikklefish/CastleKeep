#ifndef AUDITLOG_HPP
#define AUDITLOG_HPP

#include <string>
#include <chrono>
#include <fstream>

class AuditLog{

    public:
    static void Log(int transaction_id, int sender_id, int receiver_id, double amount, const std::string& timestamp);

    private:
        static const std::string log_file_path;

        static std::string FormatTimestamp(const std::chrono::system_clock::time_point& timestamp);


};


#endif