#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <unordered_map>
#include <string>
#include <mutex>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <fstream>

struct Ohlcv {
    double open = 0;
    double high = 0;
    double low = 0;
    double close = 0;
    int64_t volume = 0;

    static std::ofstream logFile;

    static void initLogFile() {
        // Open the log file once during initialization
        logFile.open("ohlcv_log.txt", std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;
        }
    }

    static void closeLogFile() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void print() const {
        if (logFile.is_open()) {
            logFile << "open: " << open
                    << ", high: " << high
                    << ", low: " << low
                    << ", close: " << close
                    << ", volume: " << volume
                    << std::endl;
        } else {
            std::cerr << "Log file is not open." << std::endl;
        }
    }
};

// Define the static logFile


// Declare the global dictionary and mutex
extern std::unordered_map<std::string, std::unordered_map<int64_t, Ohlcv>> globalMap;
extern std::mutex globalMapMutex;

// Function to start the WebSocket client
void startWebSocketClient(const std::string &uri);

#endif // WEBSOCKET_CLIENT_H
