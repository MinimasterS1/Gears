#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <deque>


class Logger {
public:

    enum class LogLevel {
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        INPUT,
        CLEAR,
        DESTROY
    };

    struct LogEntry {

        LogLevel level;
        std::string message;
        double Num;
    };

    void Log(LogLevel level, const std::string& message, double Num);

    const std::deque<LogEntry>& GetLogs() const;

private:

    std::deque<LogEntry> logs;

    const size_t maxLogCount = 100;
};


#endif