#pragma once

class Datacenter {
private:
    float actualTemperature;
    float actualHumidity;
    float desiredTemperature; 
    float desiredHumidity;    

public:
    Datacenter()
        : actualTemperature(25.0), actualHumidity(50.0),
          desiredTemperature(22.0), desiredHumidity(45.0) {}

    float getCurrentTemperature() const {
        return actualTemperature;
    }

    void setCurrentTemperature(float temp) {
        actualTemperature = temp;
    }

    float getCurrentHumidity() const {
        return actualHumidity;
    }

    void setCurrentHumidity(float humidity) {
        actualHumidity = humidity;
    }

    float getDesiredTemperature() const { 
        return desiredTemperature;
    }

    void setDesiredTemperature(float temp) { 
        desiredTemperature = temp;
    }

    float getDesiredHumidity() const { 
        return desiredHumidity;
    }

    void setDesiredHumidity(float humidity) { 
        desiredHumidity = humidity;
    }
};