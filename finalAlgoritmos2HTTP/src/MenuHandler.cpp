#include <MenuHandler.h>
#include <iostream>
#include <MSForecastAPI.h>  

MenuHandler::MenuHandler(DatacenterClimateController& ctrl, ILogger* logged, IAlertSender& sender, crow::SimpleApp* app)
    : controller(ctrl), logger(logged), alertSender(sender), app_ptr(app) {}

void MenuHandler::displayMenu() {
    Datacenter& datacenter = controller.getDatacenter();
    MockMSForecastAPI api;
    int choice;
    do {
        std::cout << "\nDatacenter Climate Controller Menu:\n";
        std::cout << "1. Read Temperature\n";
        std::cout << "2. Read Humidity\n";
        std::cout << "3. Increase Temperature( if desired > actual)\n";
        std::cout << "4. Decrease Temperature( if desired < actual)\n";
        std::cout << "5. Increase Humidity\n";
        std::cout << "6. Decrease Humidity\n";
        std::cout << "7. Change Desired Temperature\n";
        std::cout << "8. Change Desired Humidity\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                controller.readTemp(api);
                break;
            case 2:
                controller.readHumid(api);
                break;
            case 3:
                controller.increaseTemp(api);
                logger->addLog(datacenter.getCurrentHumidity(), datacenter.getCurrentTemperature());
                logger->showLogs();
                alertSender.sendAlert();
                break;
            case 4:
                controller.decreaseTemp(api);
                logger->addLog(datacenter.getCurrentHumidity(), datacenter.getCurrentTemperature());
                logger->showLogs();
                alertSender.sendAlert();
                break;
            case 5:
                controller.increaseHumid(api);
                logger->addLog(datacenter.getCurrentHumidity(), datacenter.getCurrentTemperature());
                logger->showLogs();
                alertSender.sendAlert();
                break;
            case 6:
                controller.decreaseHumid(api);
                logger->addLog(datacenter.getCurrentHumidity(), datacenter.getCurrentTemperature());
                logger->showLogs();
                alertSender.sendAlert();
                break;
            case 7: {
                float temp;
                std::cout << "Enter desired temperature: ";
                std::cin >> temp;
                controller.changeDesiredTemperature(temp);
                break;
            }
            case 8: {
                float humidity;
                std::cout << "Enter desired humidity: ";
                std::cin >> humidity;
                controller.changeDesiredHumidity(humidity);
                break;
            }
            case 9:
                std::cout << "Exiting...\n";
                if (app_ptr) { 
                    app_ptr->stop(); 
                    std::cout << "Servidor Crow detenido.\n";
                }
                break;
            default:
                std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 9);
}