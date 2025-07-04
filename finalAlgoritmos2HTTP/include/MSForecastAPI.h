#pragma once

class MSForecastAPI {
public: 
    virtual ~MSForecastAPI() = default;
    virtual void Up_Temp(int X, float& currentTemp, float desiredTemp) = 0;
    virtual void Down_Temp(int X, float& currentTemp, float desiredTemp) = 0;
    virtual void Up_Humidity(int X, float& currentTemp, float desiredTemp) = 0;
    virtual void Down_Humidity(int X, float& currentTemp, float desiredTemp) = 0;
    virtual float Read_Temp(float currentTemp) = 0;
    virtual float Read_Humidity(float currentHumidity) = 0;
};

class MockMSForecastAPI : public MSForecastAPI {
public:
    void Up_Temp(int X, float& currentTemp, float desiredTemp) override {
        if (currentTemp < desiredTemp) {  
            currentTemp = desiredTemp;  
        }
    }

    void Down_Temp(int X, float& currentTemp, float desiredTemp) override {
        if (currentTemp > desiredTemp) {  
            currentTemp = desiredTemp;  
        }
    }

    void Up_Humidity(int X, float& currentHumidity, float desiredHumidity) override {
        if (currentHumidity < desiredHumidity) {  
            currentHumidity = desiredHumidity; 
        }
    }

    void Down_Humidity(int X, float& currentHumidity, float desiredHumidity) override {
        if (currentHumidity > desiredHumidity) { 
            currentHumidity = desiredHumidity;  
        }
    }


    float Read_Temp(float currentTemp) override {
        return currentTemp;  
    }

    float Read_Humidity(float currentHumidity) override {
        return currentHumidity;  
    }
};