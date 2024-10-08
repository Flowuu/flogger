# flogger

## Overview

**flogger** is a simple and effective C++ logging library designed for Windows console applications. It allows logging of messages with different severity levels, supports color-coded output, and includes timestamps in each log entry. It also provides console management functions like clearing the screen and showing or hiding the cursor.

## Features

- **Logging with Levels**: Supports logging messages with different severity levels (INFO, WARNING, ERROR, etc.).
- **Color-coded Output**: Outputs messages in different colors based on the log level.
- **Timestamps**: Automatically adds a timestamp to each log message.
- **Console Title**: Can set the console window title.
- **Console Management**: 
  - Clears the console screen.
  - Shows or hides the console cursor.
- **Automatic Console Management**: Automatically allocates and frees the console resources.

## Installation

Simply include the `flogger.hpp` header file in your project:

## Example
```cpp
fLog console("Debug Win");

console.log("This is flogger");

console.timestamp();

console.log(logLevel::RED,          "This is log with color RED");
console.log(logLevel::LIGHTGREEN,   "This is log with color LIGHTGREEN");
console.log(logLevel::CYAN,         "This is log with color CYAN\n\n");

console.timestamp();

console.report(logLevel::INFO,      "This is report with INFO");
console.report(logLevel::WARNING,   "This is report with WARNING");
console.report(logLevel::ERR,       "This is report with ERR\n\n");


DWORD hex = 0xffff;

console.logWithTitle(logLevel::RED,          "Title", "0x%x", hex);
console.logWithTitle(logLevel::LIGHTRED,     "Title", "0x%x", hex);
console.logWithTitle(logLevel::LIGHTMAGENTA, "Title", "0x%x", hex);

console.showCursor(false);
```
![image](https://github.com/user-attachments/assets/0885167e-3c0d-4320-8ec1-bbbf261b32aa)

