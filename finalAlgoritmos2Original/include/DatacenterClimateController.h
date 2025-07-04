#pragma once

#include <MSForecastAPI.h>
#include <AlertSender.h>
#include <Logger.h>
#include <memory>
#include <Datacenter.h>

class DatacenterClimateController {
private:
    Datacenter& datacenter;

public:
    DatacenterClimateController(Datacenter& dc);
    Datacenter& getDatacenter();

    void readTemp(MSForecastAPI& api);
    void readHumid(MSForecastAPI& api);
    void increaseTemp(MSForecastAPI& api);
    void decreaseTemp(MSForecastAPI& api);
    void increaseHumid(MSForecastAPI& api);
    void decreaseHumid(MSForecastAPI& api);
    void changeDesiredTemperature(float temp);
    void changeDesiredHumidity(float humidity);
};