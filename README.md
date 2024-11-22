# fLogger

**fLogger** is a lightweight, customizable logging utility for C++ applications on Windows. It provides flexible console management, color-coded logging, and various log levels for enhanced readability and debugging.

---

## Features

- **Console Management**: Allocate and manage a dedicated console for logging.
- **Log Levels**: Supports multiple levels of logging (e.g., `info`, `warn`, `error`, `success`).
- **Color-Coded Logs**: Customizable colors for different log levels.
- **Timestamps**: Toggleable timestamps for log messages.
- **Cursor Visibility Control**: Show or hide the console cursor.
- **Easy Integration**: Simple setup and usage in any C++ project.

---

## Getting Started

### Prerequisites

- Windows OS
- C++ compiler supporting C++11 or later
- Windows SDK for `Windows.h`

### Installation

1. Download the `fLogger.hpp` file.
2. Place it in your project directory.
3. Include it in your source code:

## Usage
### Example
```cpp
    FLog console("My Application");
    
    // LOG_ERROR_AT Usage
    if (error)
        LOG_ERROR_AT(console);
    
    // Basic logging
    console.log("\n\nFlower\n");
    console.log(LogLevel::green, "Green Flower\n\n");
    
    // Report logging
    console.report(LogLevel::info, "This is an informational message.\n");
    console.report(LogLevel::warn, "This is an warn message.\n");
    console.report(LogLevel::error, "An error occurred!\n");
    console.report(LogLevel::success, "successfully logged!\n");
    console.report(LogLevel::magenta, ".etc\n\n");
    
    // Loggin with custom title
    console.logWithTitle(LogLevel::cyan, "Title", "logs\n\n");
    
    system("pause");
    
    // Clear console screen
    console.clear();
    console.report(LogLevel::magenta, "Cleared console.\n\n");
    
    // Toggle timestamps for log messages
    console.toggleTimestamp();
    console.log("This is white message.\n");
    console.log(LogLevel::red, "This is red message.\n");
    console.log(LogLevel::green, "This is green message.\n");
    console.log(LogLevel::blue, "This is blue message.\n\n");
```

---

### Global Console Usage
- If `GLOBAL_CONSOLE` is enabled, you can use the global console instance:
```cpp
    console->log("Global log instance is available!\n");
    console->report(LogLevel::warn, "This is a warning message.\n");
```

---

### `LOG_ERROR_AT` Usage
- Logs function name and line number:
```cpp
    if (error) {
        LOG_ERROR_AT(console);
    
        // If GLOBAL_CONSOLE is enabled
        LOG_ERROR_AT();
    }
```

---

### Basic logging
- Prints text on console screen:
```cpp
    console.log("Flower\n");
    console.log(LogLevel::green, "Green Flower\n");
```

---

### Report logging
- Prints text with report icons:
```cpp
    console.report(LogLevel::info, "This is an informational message.\n");
    console.report(LogLevel::warn, "This is an warn message.\n");
    console.report(LogLevel::error, "An error occurred!\n");
    console.report(LogLevel::success, "successfully logged!\n");
    console.report(LogLevel::magenta, ".etc\n");
```

---

### Log with custom title
- Prints text with custom title:
```cpp
    console.logWithTitle(LogLevel::cyan, "Title", "logs\n");
```

---

### Clearing the Console
- Clear the console screen:
```cpp
    console.clear();
```

---

### Enabling Timestamps
- Toggle timestamps for log messages:
```cpp
    console.toggleTimestamp();
```

## Configuration
- DISABLE_LOGGING: Disable all logging (default: 0).
- ALLOCATE_CONSOLE: Automatically allocate a console (default: 1).
- GLOBAL_CONSOLE: Enable a global console instance (default: 1).

## Screenshots
![image](https://github.com/user-attachments/assets/e026732d-ff5e-467d-a8ff-991da0279e38)
![image](https://github.com/user-attachments/assets/a6b680bc-3156-4f62-b7ad-6c376f729e46)

## License
This project is licensed under the MIT License. See [LICENSE](https://github.com/Flowuu/fLogger/blob/main/LICENSE) for details.

## Contributing
Contributions are welcome! Feel free to submit pull requests or report issues.
