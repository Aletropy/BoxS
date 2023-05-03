#pragma once

#include <stdarg.h>

namespace BoxS
{
    class Logger
    {
    public:
        Logger() = delete;
        Logger(const Logger&& other) = delete;

        static void Info(const char* message, ...);
        static void Warn(const char* message, ...);
        static void Error(const char* message, ...);

    private:
        enum class ConsoleColor
        {
            Black = 0,
            Red = 1,
            Green = 2,
            Yellow = 3,
            Blue = 4,
            Magenta = 5,
            Cyan = 6,
            White = 7
        };

        static void Log(const char* level, const char* message, va_list args);
        static void ChangeConsoleColor(ConsoleColor color);
    };
}