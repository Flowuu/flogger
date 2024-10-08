```
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

![image](https://github.com/user-attachments/assets/673914f3-8b1e-4245-ae8b-e99921c6eccf)
