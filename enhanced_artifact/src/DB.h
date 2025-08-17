#ifndef DB_H
#define DB_H

#include <string>
#include <cstdint>

struct ExceptionEvent;

struct sqlite3;       // forward decl (from SQLite C API)
struct sqlite3_stmt;  // forward decl

/**
 * @brief Lightweight RAII wrapper around SQLite3 to log exception events.
 *        Databases: parameterized inserts, schema init, simple query helpers.
 */
class DB {
public:
    explicit DB(const std::string& path);
    ~DB();

    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;

    bool init_schema();
    bool insert_event(const ExceptionEvent& ev);
    std::int64_t count_events() const;

private:
    sqlite3* db_ = nullptr;
    mutable sqlite3_stmt* count_stmt_ = nullptr;
};

#endif // DB_H
