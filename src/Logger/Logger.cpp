#include "Logger.h"
#include <ctime>
#include <iostream>

std::vector<LogEntry> Logger::messages;

std::string curDateTimeStr(){
    // alternate method using chrono
    // std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    // std::string output(30, '\0');
    // std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));

    std::time_t timestamp = std::time(NULL);                                            // create timestamp for current day/time
    struct std::tm datetime = *std::localtime(&timestamp);                              // convert timestamp to tm struct in local time zone
    char output[30];                                                                    // create string to hold formatted datetime string
    std::strftime(output, 30, "%d-%b-%Y %H:%M:%S", &datetime);                          // format datetime string

    return output;                                                                      // return formatted datetime string
}

void Logger::Log(const std::string& message){
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG [ " + curDateTimeStr() + " ] - " + message;                 // generate output string
    std::cout << "\x1B[1;32m" <<  logEntry.message << "\x1B[0m" << std::endl;           // send string to cout
    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message){
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR [ " + curDateTimeStr() + " ] - " + message;                 // generate log output string
    std::cout << "\x1B[1;31m" <<  logEntry.message << "\x1B[0m" << std::endl;           // send string to cout
    messages.push_back(logEntry);
}
