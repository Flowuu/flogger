#ifndef flogger
#define flogger

#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <cstdarg>
#include <chrono>
#include <ctime>

enum class logLevel {
    INFO            = 11,
    WARNING         = 6,
    ERR             = 4,
    BLACK           = 0,
    BLUE            = 1,
    GREEN           = 2,
    CYAN            = 3,
    RED             = 4,
    MAGENTA         = 5,
    ORANGE          = 6,
    LIGHTGRAY       = 7,
    DARKGRAY        = 8,
    LIGHTBLUE       = 9,
    LIGHTGREEN      = 10,
    LIGHTCYAN       = 11,
    LIGHTRED        = 12,
    LIGHTMAGENTA    = 13,
    YELLOW          = 14,
    WHITE           = 15
};

class fLog {

private:
    FILE* filePointer = nullptr;
    bool timestampToggle = false;

    void resetColor() {
        setColor(logLevel::WHITE);
    }

    void printTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm* localTime = std::localtime(&time);

        std::cout << "[" << std::put_time(localTime, "%H:%M:%S") << "] ";
    }

public:
    fLog() {
        AllocConsole();
        freopen_s(&filePointer, "CONOUT$", "w", stdout);
    }

    fLog(const char* title) : fLog() {
        SetConsoleTitleA(title);
    }

    ~fLog() {
        close();
    }

    void close() {
        if (filePointer) {
            fclose(filePointer);
            FreeConsole();
            filePointer = nullptr;
        }
    }

    void clear() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        DWORD written;
        COORD coord = { 0, 0 };

        GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
        DWORD cells = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;

        FillConsoleOutputCharacter(hConsole, ' ', cells, coord, &written);

        GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

        SetConsoleCursorPosition(hConsole, coord);
    }

    void setColor(logLevel level) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(level));
    }

    void log(const char* format, ...) {
        if(timestampToggle)
            printTimestamp();

        va_list args;
        va_start(args, format);

        vprintf(format, args);

        va_end(args);

        resetColor();
        std::cout << std::endl;
    }

    void log(logLevel level, const char* format, ...) {
        setColor(level);

        if (timestampToggle)
            printTimestamp();

        va_list args;
        va_start(args, format);

        vprintf(format, args);

        va_end(args);

        resetColor();
        std::cout << std::endl;
    }

    void logWithTitle(logLevel level, const char* title, const char* format, ...) {
        setColor(level);

        if (timestampToggle)
            printTimestamp();

        std::cout << "|" << title << "| ";
        resetColor();

        va_list args;
        va_start(args, format);

        vprintf(format, args);

        va_end(args);

        std::cout << std::endl;
    }

    void report(logLevel level, const char* format, ...) {
        const char* title = nullptr;

        switch (level) {
        case logLevel::INFO:    title = "Info   "; break;
        case logLevel::WARNING: title = "Warning"; break;
        case logLevel::ERR:     title = "Error  "; break;
        }

        logWithTitle(level, title, format);
    }

    void showCursor(bool show) {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;

        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = show;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void timestamp() {
        timestampToggle =! timestampToggle;
    }
};

#endif
