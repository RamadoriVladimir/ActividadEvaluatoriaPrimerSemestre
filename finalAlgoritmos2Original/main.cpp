#include <MenuHandler.h>
#include <AlertSender.h>
#include <Datacenter.h>
#include <DatacenterClimateController.h>
#include <Logger.h>

int main() {
    Datacenter datacenter;
    auto alertSender = std::unique_ptr<IAlertSender>(new MailAlertSender());
    Logger logger;
    DatacenterClimateController controller(datacenter);
    MenuHandler menu(controller, &logger, *alertSender);

    menu.displayMenu();

    return 0;
}