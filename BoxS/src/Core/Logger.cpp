#include "boxspch.h"
#include "Logger.h"

namespace BoxS
{
    void Logger::Info(const char* message, ...)
    {
        va_list args;
        va_start(args, message);
        ChangeConsoleColor(ConsoleColor::Cyan);
        Log("INFO", message, args);
        va_end(args);
    }

    void Logger::Warn(const char* message, ...)
    {
        va_list args;
        va_start(args, message);
        ChangeConsoleColor(ConsoleColor::Yellow);
        Log("WARN", message, args);
        va_end(args);
    }

    void Logger::Error(const char* message, ...)
    {
        va_list args;
        va_start(args, message);
        ChangeConsoleColor(ConsoleColor::Red);
        Log("ERROR", message, args);
        va_end(args);
    }

    void Logger::Log(const char* level, const char* message, va_list args)
    {
        std::cout << "[BoxS | " << level << "] ";
        vprintf(message, args);
        std::cout << std::endl;
        ChangeConsoleColor(ConsoleColor::White);
    }    

    void Logger::ChangeConsoleColor(ConsoleColor color)
    {
        int fg = static_cast<int>(color);
        std::cout << "\033[3" << fg << "m";
    }
}