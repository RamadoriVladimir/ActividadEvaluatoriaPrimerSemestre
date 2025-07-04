#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <chrono>   
#include <ctime>    
#include <iomanip>  
#include <sstream>  
#include <SqliteDatabaseHandler.h>
#include <stdexcept> 

typedef struct Log {
    float humidity;
    float temperature;
    std::string dateTime;

    Log(float humidity, float temperature, const std::string& dateTime) : humidity(humidity), temperature(temperature), dateTime(dateTime) {}
} Log;

class ILogger{
    public:
        virtual void addLog(float humidity, float temperature) = 0;
        virtual std::vector<std::unique_ptr<Log>>& getData() = 0;
        virtual void showLogs() const = 0;
        virtual ~ILogger() = default;
};

class Logger : public ILogger {
private:
    std::vector<std::unique_ptr<Log>> logs;
    std::string getCurrentTimestamp();

public:
    Logger();
    ~Logger() override;

    void addLog(float humidity, float temperature) override;
    std::vector<std::unique_ptr<Log>>& getData() override;
    void showLogs() const override;
};

class HistoricLogger : public ILogger {
private:
    std::unique_ptr<DatabaseHandler> dbHandler;
    std::string dbPath; 
    std::vector<std::unique_ptr<Log>> currentFetchedLogs;

    void createTableIfNotExists();
    std::string getCurrentTimestamp();

public:
    HistoricLogger(const std::string& path);
    ~HistoricLogger() override;

    void addLog(float humidity, float temperature) override;
    std::vector<std::unique_ptr<Log>>& getData() override;
    void showLogs() const override;
};
