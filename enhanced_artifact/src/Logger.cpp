#include "Logger.h"
#include "DB.h"
#include <exception>

void Logger::log(const std::exception& ex, const std::string& where) {
    ExceptionEvent ev;
    ev.timestamp = std::chrono::system_clock::now();
    ev.type = typeid(ex).name();
    ev.message = ex.what();
    ev.where = where;
    events_.push_back(std::move(ev));
}

void Logger::log(const std::string& type, const std::string& message, const std::string& where) {
    ExceptionEvent ev;
    ev.timestamp = std::chrono::system_clock::now();
    ev.type = type;
    ev.message = message;
    ev.where = where;
    events_.push_back(std::move(ev));
}

std::size_t Logger::persist_all(DB& db) {
    std::size_t written = 0;
    for (const auto& ev : events_) {
        if (db.insert_event(ev)) {
            ++written;
        }
    }
    return written;
}
