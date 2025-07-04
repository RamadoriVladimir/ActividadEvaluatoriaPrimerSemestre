#pragma once
#include <crow_all.h>
#include <DatacenterClimateController.h>
#include <MSForecastAPI.h>
#include <Logger.h>

class HttpController {
private:
    DatacenterClimateController& controller;
    MSForecastAPI& api;
    ILogger* logger;

public:
    HttpController(DatacenterClimateController& ctrl, MSForecastAPI& apiRef, ILogger* logger_ptr);

    void registerRoutes(crow::SimpleApp& app);
};
