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

```cpp
#include "flogger.hpp"

fLog logger("Debug Win");

logger.log("This is flogger");

logger.log(logLevel::INFO,          "This is log with color INFO");
logger.log(logLevel::WARNING,       "This is log with color WARNING");
logger.log(logLevel::ERR,           "This is log with color ERR\n\n");


logger.report(logLevel::INFO,       "This is report with INFO");
logger.report(logLevel::WARNING,    "This is report with  WARNING");
logger.report(logLevel::ERR,        "This is report with ERR\n\n");


DWORD hex = 0xffff;

logger.logWithTitle(logLevel::RED,          "Title", "0x%x", hex);
logger.logWithTitle(logLevel::LIGHTRED,     "Title", "0x%x", hex);
logger.logWithTitle(logLevel::LIGHTMAGENTA, "Title", "0x%x", hex);

logger.showCursor(false);
```

![image](https://github.com/user-attachments/assets/a3927a8e-85ed-4036-8c31-487854268e49)
