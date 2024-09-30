#ifndef AUDITLOG_HPP
#define AUDITLOG_HPP

#include <string>
#include <chrono>
#include <fstream>

class AuditLog
{
private:
    static const std::string log_file_path;
public:
    static void Log(int transaction_id, const std::string &encrypted_data);

};

#endif