#include "Logger.hpp"

Logger::Logger(bool verbose, const std::string& logFilePath)
    : m_verbose(verbose) {
    if (!logFilePath.empty()) {
        m_logFile.open(logFilePath, std::ios::out | std::ios::app);
        if (!m_logFile) {
            std::cerr << "Error: Could not open log file: " << logFilePath << std::endl;
        }
    }
}

Logger::~Logger() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void Logger::info(const std::string& message) {
    if (m_verbose) {
        std::clog << "[INFO] " << message << std::endl;
    }
    if (m_logFile) {
        m_logFile << "[INFO] " << message << std::endl;
    }
}

void Logger::debug(const std::string& message) {
    if (m_verbose) {
        std::clog << "[DEBUG] " << message << std::endl;
    }
    if (m_logFile) {
        m_logFile << "[DEBUG] " << message << std::endl;
    }
}

void Logger::error(const std::string& message) {
    if (m_verbose) {
        std::clog << "[ERROR] " << message << std::endl;
    }
    if (m_logFile) {
        m_logFile << "[ERROR] " << message << std::endl;
    }
}