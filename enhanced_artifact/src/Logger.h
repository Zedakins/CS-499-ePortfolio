#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>

class DB;

/**
 * @brief Structured record for an exception event.
 */
struct ExceptionEvent {
    std::chrono::system_clock::time_point timestamp{};
    std::string type;
    std::string message;
    std::string where;
};

/**
 * @brief In-memory logger with optional DB persistence.
 *        SDE: separation of concerns; testable, dependency-injected DB.
 */
class Logger {
public:
    void log(const std::exception& ex, const std::string& where);
    void log(const std::string& type, const std::string& message, const std::string& where);

    const std::vector<ExceptionEvent>& events() const { return events_; }

    // Persist all current events into DB.
    // Returns the number of rows successfully written.
    std::size_t persist_all(DB& db);

private:
    std::vector<ExceptionEvent> events_;
};

#endif // LOGGER_H
