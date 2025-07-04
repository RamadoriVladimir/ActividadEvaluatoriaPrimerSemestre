#include <DatacenterClimateController.h>
#include <iostream>

DatacenterClimateController::DatacenterClimateController(Datacenter& dc)
    : datacenter(dc) {}

Datacenter& DatacenterClimateController::getDatacenter() {
    return datacenter;
}

void DatacenterClimateController::readTemp(MSForecastAPI& api) {
    float temp = api.Read_Temp(datacenter.getCurrentTemperature());
    std::cout << "Current Temperature: " << temp << " Celsius degrees"  << std::endl;
}

void DatacenterClimateController::readHumid(MSForecastAPI& api) {
    float humid = api.Read_Humidity(datacenter.getCurrentHumidity());
    std::cout << "Current Humidity: " << humid << "%" << std::endl;
}

void DatacenterClimateController::increaseTemp(MSForecastAPI& api) {
    float temp = datacenter.getCurrentTemperature();
    float desiredTemp = datacenter.getDesiredTemperature();
    api.Up_Temp(1, temp, desiredTemp);
    datacenter.setCurrentTemperature(temp);
    std::cout << "Temperature adjusted. Current: " << temp << " Desired: " << desiredTemp << " Celsius degrees" << std::endl;
}

void DatacenterClimateController::decreaseTemp(MSForecastAPI& api) {
    float temp = datacenter.getCurrentTemperature();
    float desiredTemp = datacenter.getDesiredTemperature();
    api.Down_Temp(1, temp, desiredTemp);
    datacenter.setCurrentTemperature(temp);
    std::cout << "Temperature adjusted. Current: " << temp << " Desired: " << desiredTemp << " Celsius degrees" << std::endl;
}

void DatacenterClimateController::increaseHumid(MSForecastAPI& api) {
    float humid = datacenter.getCurrentHumidity();
    float desiredHumid = datacenter.getDesiredHumidity();
    api.Up_Humidity(1, humid, desiredHumid);
    datacenter.setCurrentHumidity(humid);
    std::cout << "Humidity adjusted. Current: " << humid << " Desired: " << desiredHumid << "%" << std::endl;
}

void DatacenterClimateController::decreaseHumid(MSForecastAPI& api) {
    float humid = datacenter.getCurrentHumidity();
    float desiredHumid = datacenter.getDesiredHumidity();
    api.Down_Humidity(1, humid, desiredHumid);
    datacenter.setCurrentHumidity(humid);
    std::cout << "Humidity adjusted. Current: " << humid << " Desired: " << desiredHumid << "%" << std::endl;
}

void DatacenterClimateController::changeDesiredTemperature(float temp) {
    datacenter.setDesiredTemperature(temp);
    std::cout << "Desired temperature set to: " << temp << " Celsius degrees.\n";
}

void DatacenterClimateController::changeDesiredHumidity(float humidity) {
    datacenter.setDesiredHumidity(humidity);
    std::cout << "Desired humidity set to: " << humidity << "%.\n";
}