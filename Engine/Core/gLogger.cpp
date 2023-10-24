#include "gLogger.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Logger::Log(LogLevel level, const std::string& message, double num) {
    
    LogEntry entry;
    entry.level = level;

   
    if (level == LogLevel::ERROR || level == LogLevel::WARNING) {
        std::ostringstream locationInfo;
        locationInfo << "File: " << __FILE__ << ", Line: " << __LINE__;
        entry.message = locationInfo.str() + " | Description: " + message;
    }
    else {
        entry.message = message;
    }

  
    entry.message += "| Value  " + std::to_string(num);

  
    logs.push_back(entry);

   
    while (logs.size() > maxLogCount) {
        logs.pop_front();
    }

   
    switch (level) {
    case LogLevel::ERROR:
        std::cerr << "ERROR: " << entry.message << std::endl;
        break;
    case LogLevel::WARNING:
        std::cerr << "WARNING: " << entry.message << std::endl;
        break;
    case LogLevel::INFO:
        std::cout << "INFO: " << entry.message << std::endl;
        break;
    case LogLevel::DEBUG:
        std::cout << "DEBUG: " << entry.message << std::endl;
        break;
    case LogLevel::INPUT:
        std::cout << "INPUT: " << entry.message << std::endl;
        break;
    case LogLevel::CLEAR:
        std::cout << "CLEAR: " << entry.message << std::endl;
        break;
    case LogLevel::DESTROY:
        std::cout << "DESTROY: " << entry.message << std::endl;
        break;
    }

   
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << entry.message << std::endl;
        logFile.close();
    }
}
