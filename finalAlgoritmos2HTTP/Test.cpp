#include <TestEvaluator.hpp>
#include <Datacenter.h>
#include <DatacenterClimateController.h>
#include <MSForecastAPI.h>

int main() {
    TestEvaluator te;
    te.title("DatacenterClimateController Tests");

    // Test 1: Increase temperature
    {
        Datacenter dc;
        dc.setCurrentTemperature(20.0f);
        MockMSForecastAPI api;
        DatacenterClimateController controller(dc);

        controller.increaseTemp(api);

        float result = dc.getCurrentTemperature();
        te.evaluate("Temperature should be set to desired value", result == 22.0f);
    }

    // Test 2: Decrease humidity
    {
        Datacenter dc;
        dc.setCurrentHumidity(60.0f);
        MockMSForecastAPI api;
        DatacenterClimateController controller(dc);

        controller.decreaseHumid(api);

        float result = dc.getCurrentHumidity();
        te.evaluate("Humidity should be set to desired value", result == 45.0f);
    }

    te.summary();
    return 0;
}