#pragma once 
#include <string>
#include <vector>
#include <iostream>
#include <memory>

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

public:
    Logger() = default;
    ~Logger() = default;

    void addLog(float humidity, float temperature) override {
        std::string dateTime = "2024-12-09 12:00:00"; 
        logs.push_back(std::make_unique<Log>(humidity, temperature, dateTime));
    }

    std::vector<std::unique_ptr<Log>>& getData() override {
        return logs;
    }
    
    void showLogs() const override {
        std::cout << "\nHumidity Log History:\n";
        for (const auto& log : logs) {
            std::cout << "Humidity: " << log->humidity << "% at " << log->dateTime << std::endl;
        }
        std::cout << "\nTemperature Log History:\n";
        for (const auto& log : logs) {
            std::cout << "Temperature: " << log->temperature << " at " << log->dateTime << std::endl;
        }
    }
};
