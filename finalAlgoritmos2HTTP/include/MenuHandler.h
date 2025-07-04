#pragma once
#include <DatacenterClimateController.h>
#include <crow_all.h>

class MenuHandler {
private:
    DatacenterClimateController& controller;
    ILogger* logger;
    IAlertSender& alertSender;
    crow::SimpleApp* app_ptr; 

public:
    MenuHandler(DatacenterClimateController& ctrl, ILogger* logged, IAlertSender& sender, crow::SimpleApp* app);

    void displayMenu();
};
