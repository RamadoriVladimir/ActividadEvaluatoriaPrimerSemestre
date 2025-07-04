#include <HttpController.h>
#include <iostream>

HttpController::HttpController(DatacenterClimateController& ctrl, MSForecastAPI& apiRef, ILogger* logger_ptr)
    : controller(ctrl), api(apiRef), logger(logger_ptr) {}

void HttpController::registerRoutes(crow::SimpleApp& app) {
    using namespace crow;

    CROW_ROUTE(app, "/get_current_climate").methods("GET"_method, "OPTIONS"_method)(
        [this](const request& req, response& res) {
            CROW_LOG_INFO << "Recibida solicitud a /get_current_climate. Método: " << crow::method_name(req.method);

            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "GET, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");

            if (req.method == "OPTIONS"_method) {
                CROW_LOG_INFO << "Manejando solicitud OPTIONS para /get_current_climate. Enviando 204 No Content.";
                res.code = 204;
                res.end();
                return;
            }

            json::wvalue res_json;
            res_json["current_temperature"] = controller.getDatacenter().getCurrentTemperature();
            res_json["current_humidity"] = controller.getDatacenter().getCurrentHumidity();

            res.code = 200;
            res.add_header("Content-Type", "application/json");
            res.write(res_json.dump());
            res.end();
            CROW_LOG_INFO << "Respuesta exitosa (200 OK) para /get_current_climate.";
        });


    CROW_ROUTE(app, "/adjust_temperature").methods("POST"_method, "OPTIONS"_method)(
        [this](const request& req, response& res) {
            CROW_LOG_INFO << "Recibida solicitud a /adjust_temperature. Método: " << crow::method_name(req.method)
                          << ". Tamaño del cuerpo: " << req.body.length() << " bytes.";

            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");

            if (req.method == "OPTIONS"_method) {
                CROW_LOG_INFO << "Manejando solicitud OPTIONS para /adjust_temperature. Enviando 204 No Content.";
                res.code = 204;
                res.end();
                return;
            }

            CROW_LOG_INFO << "Manejando solicitud POST para /adjust_temperature. Cuerpo: " << req.body;
            auto body = json::load(req.body);

            if (!body) {
                CROW_LOG_ERROR << "Cuerpo de solicitud JSON inválido para /adjust_temperature.";
                res.code = 400;
                res.add_header("Content-Type", "text/plain");
                res.write("Invalid JSON body");
                res.end();
                return;
            }
            if (!body.has("desired_temperature")) {
                CROW_LOG_ERROR << "Falta 'desired_temperature' en el cuerpo JSON para /adjust_temperature.";
                res.code = 400;
                res.add_header("Content-Type", "text/plain");
                res.write("Invalid or missing 'desired_temperature'");
                res.end();
                return;
            }

            float desired_temp = static_cast<float>(body["desired_temperature"].d());
            controller.changeDesiredTemperature(desired_temp);

            float current_temp = controller.getDatacenter().getCurrentTemperature();
            if (desired_temp > current_temp) {
                controller.increaseTemp(api);
                CROW_LOG_INFO << "Aumentando temperatura. Deseada: " << desired_temp << ", Actual: " << current_temp;
            } else if (desired_temp < current_temp) {
                controller.decreaseTemp(api);
                CROW_LOG_INFO << "Disminuyendo temperatura. Deseada: " << desired_temp << ", Actual: " << current_temp;
            } else {
                CROW_LOG_INFO << "Temperatura ya en el valor deseado. Deseada: " << desired_temp << ", Actual: " << current_temp;
            }

            if (logger) {
                logger->addLog(controller.getDatacenter().getCurrentHumidity(), controller.getDatacenter().getCurrentTemperature());
            }

            json::wvalue res_json;
            res_json["status"] = "Temperature adjusted";
            res_json["current_temp"] = controller.getDatacenter().getCurrentTemperature();
            res_json["desired_temp"] = desired_temp;
            res_json["current_humid"] = controller.getDatacenter().getCurrentHumidity(); 

            res.code = 200;
            res.add_header("Content-Type", "application/json");
            res.write(res_json.dump());
            res.end();
            CROW_LOG_INFO << "Respuesta exitosa (200 OK) para /adjust_temperature.";
        });

    CROW_ROUTE(app, "/adjust_humidity").methods("POST"_method, "OPTIONS"_method)(
        [this](const request& req, response& res) {
            CROW_LOG_INFO << "Recibida solicitud a /adjust_humidity. Método: " << crow::method_name(req.method)
                          << ". Tamaño del cuerpo: " << req.body.length() << " bytes.";

            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");

            if (req.method == "OPTIONS"_method) {
                CROW_LOG_INFO << "Manejando solicitud OPTIONS para /adjust_humidity. Enviando 204 No Content.";
                res.code = 204;
                res.end();
                return;
            }

            CROW_LOG_INFO << "Manejando solicitud POST para /adjust_humidity. Cuerpo: " << req.body;
            auto body = json::load(req.body);

            if (!body) {
                CROW_LOG_ERROR << "Cuerpo de solicitud JSON inválido para /adjust_humidity.";
                res.code = 400;
                res.add_header("Content-Type", "text/plain");
                res.write("Invalid JSON body");
                res.end();
                return;
            }
            if (!body.has("desired_humidity")) {
                CROW_LOG_ERROR << "Falta 'desired_humidity' en el cuerpo JSON para /adjust_humidity.";
                res.code = 400;
                res.add_header("Content-Type", "text/plain");
                res.write("Invalid or missing 'desired_humidity'");
                res.end();
                return;
            }

            float desired_humid = static_cast<float>(body["desired_humidity"].d());
            controller.changeDesiredHumidity(desired_humid);

            float current_humid = controller.getDatacenter().getCurrentHumidity();
            if (desired_humid > current_humid) {
                controller.increaseHumid(api);
                CROW_LOG_INFO << "Aumentando humedad. Deseada: " << desired_humid << ", Actual: " << current_humid;
            } else if (desired_humid < current_humid) {
                controller.decreaseHumid(api);
                CROW_LOG_INFO << "Disminuyendo humedad. Deseada: " << desired_humid << ", Actual: " << current_humid;
            } else {
                CROW_LOG_INFO << "Humedad ya en el valor deseado. Deseada: " << desired_humid << ", Actual: " << current_humid;
            }

            if (logger) {
                logger->addLog(controller.getDatacenter().getCurrentHumidity(), controller.getDatacenter().getCurrentTemperature());
            }

            json::wvalue res_json;
            res_json["status"] = "Humidity adjusted";
            res_json["current_humid"] = controller.getDatacenter().getCurrentHumidity();
            res_json["desired_humid"] = desired_humid;
            res_json["current_temp"] = controller.getDatacenter().getCurrentTemperature(); 

            res.code = 200;
            res.add_header("Content-Type", "application/json");
            res.write(res_json.dump());
            res.end();
            CROW_LOG_INFO << "Respuesta exitosa (200 OK) para /adjust_humidity.";
        });
}
