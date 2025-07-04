#pragma once
#include <DatacenterClimateController.h>

class MenuHandler {
private:
    DatacenterClimateController& controller;
    ILogger* logger;
    IAlertSender& alertSender;

public:
    MenuHandler(DatacenterClimateController& ctrl, ILogger* logger, IAlertSender& sender);
    void displayMenu();
};