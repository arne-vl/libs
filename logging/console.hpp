#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

enum LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
  public:
    Logger() { logsDate = false; }
    Logger(const bool &logDate) { logsDate = logDate; }

    void log(LogLevel level, const std::string &msg) {
        if (logsDate) {
            std::cout << get_datetime_string() << " [" << level_to_string(level) << "] " << msg << std::endl;
        } else {
            std::cout << "[" << level_to_string(level) << "] " << msg << std::endl;
        }
    }

  private:
    bool logsDate;

    std::string level_to_string(LogLevel level) {
        switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "INVALID_LEVEL";
        }
    }

    std::string get_datetime_string() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        auto lt = std::localtime(&t);

        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << lt->tm_mday << "-" << std::setw(2) << (lt->tm_mon + 1) << "-"
            << (1900 + lt->tm_year) << " " << std::setw(2) << lt->tm_hour << ":" << std::setw(2) << lt->tm_min << ":"
            << std::setw(2) << lt->tm_sec;

        return oss.str();
    }
};
