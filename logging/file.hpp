#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

enum LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
  public:
    Logger(const std::string &filename) {
        logFile.open(filename);
        logsDateTime = false;
    }
    Logger(const std::string &filename, const bool &logDateTime) {
        logFile.open(filename);
        logsDateTime = logDateTime;
    }

    ~Logger() { logFile.close(); }

    void log(LogLevel level, const std::string &msg) {
        if (logsDateTime) {
            logFile << get_datetime_string() << " [" << level_to_string(level) << "] " << msg << std::endl;
        } else {
            logFile << "[" << level_to_string(level) << "] " << msg << std::endl;
        }
    }

  private:
    bool logsDateTime;
    std::ofstream logFile;

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

    void ensure_file(const std::string &filename) {
        std::ifstream f(filename.c_str());
        if (f.good()) {
            return;
        } else {
            std::ofstream logfile;
            logfile.open(filename);

            if (!logfile.is_open()) {
                std::cerr << "Failed to create logfile: " << filename << std::endl;
            }

        }
    }
};
