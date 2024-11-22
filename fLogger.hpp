/*
MIT License

Copyright (c) 2024 Flowu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef FLOGGER_HPP
#define FLOGGER_HPP

#include <iostream>
#include <Windows.h>
#include <cstdarg>
#include <memory>


// Configuration Flags
#define DISABLE_LOGGING     0
#define ALLOCATE_CONSOLE    1
#define GLOBAL_CONSOLE      1

// Logging Levels
enum class LogLevel : unsigned int {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    orange,
    lightgray,
    darkgray,
    lightblue,
    lightgreen,
    lightcyan,
    lightred,
    lightmagenta,
    yellow,
    white,

    success = lightgreen,
    info    = lightcyan,
    warn    = orange,
    error   = red,
};


class FLog {
private:
    FILE* m_filePointer     = nullptr;
    HANDLE m_consoleHandle  = nullptr;
    bool m_timestampEnabled = false;

    void resetColor() const {
        setColor(LogLevel::white);
    }

    void logMessage(LogLevel level, const char* title, const char* format, va_list args) const {
#if !DISABLE_LOGGING
        setColor(level);

        if (m_timestampEnabled)
            std::cout << __TIME__ << "| ";

        if (title) {
            std::cout << "[" << title << "] ";
            resetColor();
        }

        vprintf(format, args);
        resetColor();
#endif
    }

public:
    explicit FLog(const char* title = "Untitled") {
#if ALLOCATE_CONSOLE
    #if !DISABLE_LOGGING
            AllocConsole();
            freopen_s(&m_filePointer, "CONOUT$", "w", stdout);
    #endif
#endif
        m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (title)
            SetConsoleTitleA(title);
    }

    ~FLog() {
        destroy();
    }

    void destroy() {
#if !DISABLE_LOGGING
        if (!m_filePointer)
            return;

        fclose(m_filePointer);
        FreeConsole();
        m_filePointer = nullptr;
#endif
    }

    void clear() const {
#if !DISABLE_LOGGING
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        DWORD written;
        COORD coord{ 0 };

        if (!GetConsoleScreenBufferInfo(m_consoleHandle, &bufferInfo))
            return;

        FillConsoleOutputCharacter(m_consoleHandle, ' ', bufferInfo.dwSize.X * bufferInfo.dwSize.Y, coord, &written);
        SetConsoleCursorPosition(m_consoleHandle, coord);
#endif
    }

    void setColor(LogLevel level) const {
#if !DISABLE_LOGGING
        if (level < LogLevel::black || level > LogLevel::white)
            level = LogLevel::white;

        SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(level));
#endif
    }

    void log(const char* format, ...) const {
#if !DISABLE_LOGGING
        va_list args;
        va_start(args, format);
        logMessage(LogLevel::white, nullptr, format, args);
        va_end(args);
#endif
    }

    void log(LogLevel level, const char* format, ...) const {
#if !DISABLE_LOGGING
        va_list args;
        va_start(args, format);
        logMessage(level, nullptr, format, args);
        va_end(args);
#endif
    }

    void logWithTitle(LogLevel level, const char* title, const char* format, ...) const {
#if !DISABLE_LOGGING
        va_list args;
        va_start(args, format);
        logMessage(level, title, format, args);
        va_end(args);
#endif
    }

    void report(LogLevel level, const char* format, ...) const {
#if !DISABLE_LOGGING
        const char* title;
        switch (level) {
        case LogLevel::info:    title = "i"; break;
        case LogLevel::warn:    title = "!"; break;
        case LogLevel::error:   title = "-"; break;
        case LogLevel::success: title = "+"; break;
        default:                title = ">"; break;
        }

        va_list args;
        va_start(args, format);
        logMessage(level, title, format, args);
        va_end(args);
#endif
    }

    void toggleTimestamp() {
#if !DISABLE_LOGGING
        m_timestampEnabled = !m_timestampEnabled;
#endif
    }

    void showCursor(bool visible) {
#if !DISABLE_LOGGING
        CONSOLE_CURSOR_INFO cursorInfo;
        if (!GetConsoleCursorInfo(m_consoleHandle, &cursorInfo))
            return;

        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(m_consoleHandle, &cursorInfo);
#endif
    }
};

#if GLOBAL_CONSOLE
inline std::unique_ptr<FLog> console = std::make_unique<FLog>(nullptr);

#define LOG_ERROR_AT() \
    console->report(LogLevel::error, "%s -> %d\n", __FUNCSIG__, __LINE__)
#else
#define LOG_ERROR_AT(instance) \
    instance.report(LogLevel::error, "%s -> %d\n", __FUNCSIG__, __LINE__)
#endif // !GLOBAL_CONSOLE

#endif // FLOGGER_HPP
