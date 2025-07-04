#define CROW_MAIN
#include <crow_all.h>

#include <MenuHandler.h>
#include <AlertSender.h>
#include <Datacenter.h>
#include <DatacenterClimateController.h>
#include <Logger.h> 
#include <HttpController.h>
#include <MSForecastAPI.h>
#include <iostream>
#include <thread>

int main() {
    crow::SimpleApp app;

    Datacenter datacenter;
    auto alertSender = std::make_unique<MailAlertSender>();
    HistoricLogger logger("logs.db");
    DatacenterClimateController controller(datacenter);
    MenuHandler menu(controller, &logger, *alertSender, &app);
    MockMSForecastAPI msForecastApi;
    HttpController httpController(controller, msForecastApi, &logger);

    httpController.registerRoutes(app);

    std::cout << "Iniciando servidor Crow en http://localhost:18080 en un hilo separado...\n";
    std::thread crow_thread([&]() {
        app.port(18080).multithreaded().run();
    });

    menu.displayMenu();
    crow_thread.join();

    std::cout << "Aplicación finalizada.\n";

    return 0;
}
