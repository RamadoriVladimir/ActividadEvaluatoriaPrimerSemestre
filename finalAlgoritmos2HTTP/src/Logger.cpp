#include <logger.h>

Logger::Logger() = default;
Logger::~Logger() = default;

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
};

void Logger::addLog(float humidity, float temperature) {
    std::string dateTime = getCurrentTimestamp();
    logs.push_back(std::make_unique<Log>(humidity, temperature, dateTime));
    std::cout << "Log added (in-memory): Temp=" << temperature << ", Humidity=" << humidity << " at " << dateTime << std::endl;
};

std::vector<std::unique_ptr<Log>>& Logger::getData() {
    return logs;
};

void Logger::showLogs() const {
    std::cout << "\n--- Current Logs (In-Memory) ---\n";
    if (logs.empty()) {
        std::cout << "No logs available.\n";
        return;
    }
    for (const auto& log : logs) {
        std::cout << "Timestamp: " << log->dateTime
                    << ", Temperature: " << log->temperature
                    << ", Humidity: " << log->humidity << std::endl;
    }
    std::cout << "---------------------------------\n";
};

// HistoricLogger implementation

HistoricLogger::HistoricLogger(const std::string& path) : dbPath(path) {
    dbHandler = std::make_unique<SqliteDatabaseHandler>(dbPath);
    createTableIfNotExists(); 
}

HistoricLogger::~HistoricLogger() = default;

void HistoricLogger::createTableIfNotExists() {
    std::string createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TEXT NOT NULL,
            humidity REAL NOT NULL,
            temperature REAL NOT NULL
        );
    )";
    dbHandler->prepareQuery(createTableSQL);
    dbHandler->execute();
    if (dbHandler->getErrorStatus()) {
        std::cerr << "Error creating logs table: " << dbHandler->getErrorStatus() << std::endl;
    }
}
    
std::string HistoricLogger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void HistoricLogger::addLog(float humidity, float temperature) {
    std::string timestamp = getCurrentTimestamp();

    std::string insertSQL = "INSERT INTO logs (timestamp, humidity, temperature) VALUES (?, ?, ?);";
    dbHandler->prepareQuery(insertSQL);
    dbHandler->addParameter(1, timestamp);
    dbHandler->addParameter(2, std::to_string(humidity));
    dbHandler->addParameter(3, std::to_string(temperature));
    dbHandler->execute();

    if (dbHandler->getErrorStatus()) {
        std::cerr << "Error adding log to database: " << timestamp << ", " << humidity << ", " << temperature << std::endl;
    } else {
        std::cout << "Log added to database: Temp=" << temperature << ", Humidity=" << humidity << " at " << timestamp << std::endl;
    }
}

std::vector<std::unique_ptr<Log>>& HistoricLogger::getData() {
    currentFetchedLogs.clear(); 
    std::string selectSQL = "SELECT timestamp, humidity, temperature FROM logs ORDER BY timestamp ASC;";
    dbHandler->prepareQuery(selectSQL);
    
    Table resultTable = dbHandler->fetchAll(); 

    for (const auto& row : resultTable) {
        try {
            std::string ts = row.at("timestamp");
            float hum = std::stof(row.at("humidity"));
            float temp = std::stof(row.at("temperature"));
            currentFetchedLogs.push_back(std::make_unique<Log>(hum, temp, ts)); 
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Column not found in database row: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid argument for stof conversion: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "An unexpected error occurred while processing log data: " << e.what() << std::endl;
        }
    }
    
    if (dbHandler->getErrorStatus()) {
        std::cerr << "Error fetching logs from database.\n";
    }
    return currentFetchedLogs;
}

void HistoricLogger::showLogs() const {
    std::vector<std::unique_ptr<Log>>& logsToShow = const_cast<HistoricLogger*>(this)->getData();
    
    std::cout << "\n--- Historic Logs (From Database) ---\n";
    if (logsToShow.empty()) {
        std::cout << "No historic logs available.\n";
        return;
    }
    std::cout << "\nTemperature Log History:\n";
    for (const auto& log : logsToShow) {
        std::cout << "Temperature: " << log->temperature << " at " << log->dateTime << std::endl;
    }
    std::cout << "\nHumidity Log History:\n";
    for (const auto& log : logsToShow) {
        std::cout << "Humidity: " << log->humidity << "% at " << log->dateTime << std::endl;
    }
    std::cout << "-------------------------------------\n";
}