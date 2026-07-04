#include <iostream>
using namespace std;

// Abstract Logger class - defines the chain structure
class LogProcessor
{
protected:
    int level;
    LogProcessor *nextLoggerProcessor;

public:
    static const int DEBUG = 1;
    static const int INFO = 2;
    static const int ERROR = 3;
    static const int FATAL = 4;

    void setNextLogger(LogProcessor *nextLogger)
    {
        this->nextLoggerProcessor = nextLogger;
    }

    void logMessage(int level, string message)
    {
        if (this->level <= level)
        {
            write(message);
        }

        if (this->nextLoggerProcessor != nullptr)
        {
            this->nextLoggerProcessor->logMessage(level, message);
        }
    }

    virtual void write(string message) = 0;

    virtual ~LogProcessor() {}
};

class DebugLogProcessor : public LogProcessor
{
public:
    DebugLogProcessor(int level)
    {
        this->level = level;
    }

    void write(string message) override
    {
        cout << "DEBUG: " << message << endl;
    }
};

class InfoLogProcessor : public LogProcessor
{
public:
    InfoLogProcessor(int level)
    {
        this->level = level;
    }

    void write(string message) override
    {
        cout << "INFO: " << message << endl;
    }
};

class ErrorLogProcessor : public LogProcessor
{
public:
    ErrorLogProcessor(int level)
    {
        this->level = level;
    }

    void write(string message) override
    {
        cout << "ERROR: " << message << endl;
    }
};

class FatalLogProcessor : public LogProcessor
{
public:
    FatalLogProcessor(int level)
    {
        this->level = level;
    }

    void write(string message) override
    {
        cout << "FATAL: " << message << endl;
    }
};

LogProcessor *getChainOfLoggers()
{
    LogProcessor *fatalLogger = new FatalLogProcessor(LogProcessor::FATAL);
    LogProcessor *errorLogger = new ErrorLogProcessor(LogProcessor::ERROR);
    LogProcessor *infoLogger = new InfoLogProcessor(LogProcessor::INFO);
    LogProcessor *debugLogger = new DebugLogProcessor(LogProcessor::DEBUG);

    // Debug->Info->Error->Fatal
    debugLogger->setNextLogger(infoLogger);
    infoLogger->setNextLogger(errorLogger);
    errorLogger->setNextLogger(fatalLogger);

    return debugLogger;
}
int main()
{
    LogProcessor *logProcessor = getChainOfLoggers();

    cout << "===== DEBUG =====" << endl;
    logProcessor->logMessage(LogProcessor::DEBUG, "This is a debug message");

    cout << "\n===== INFO =====" << endl;
    logProcessor->logMessage(LogProcessor::INFO, "This is an info message");

    cout << "\n===== ERROR =====" << endl;
    logProcessor->logMessage(LogProcessor::ERROR, "This is an error message");

    cout << "\n===== FATAL =====" << endl;
    logProcessor->logMessage(LogProcessor::FATAL, "This is a fatal message");

    return 0;
}