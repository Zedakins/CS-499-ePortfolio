#include "DB.h"
#include "Logger.h"
#include <sqlite3.h>
#include <chrono>

DB::DB(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
        db_ = nullptr;
    }
}

DB::~DB() {
    if (count_stmt_) {
        sqlite3_finalize(count_stmt_);
        count_stmt_ = nullptr;
    }
    if (db_) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

bool DB::init_schema() {
    if (!db_) return false;

    static const char* ddl = R"SQL(
        CREATE TABLE IF NOT EXISTS ExceptionsLog (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ts_utc TEXT NOT NULL,
            type TEXT NOT NULL,
            message TEXT NOT NULL,
            location TEXT NOT NULL
        );
    )SQL";

    char* errmsg = nullptr;
    int rc = sqlite3_exec(db_, ddl, nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK) {
        if (errmsg) sqlite3_free(errmsg);
        return false;
    }
    return true;
}

bool DB::insert_event(const ExceptionEvent& ev) {
    if (!db_) return false;

    static const char* sql = R"SQL(
        INSERT INTO ExceptionsLog (ts_utc, type, message, location)
        VALUES (?, ?, ?, ?);
    )SQL";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    // Format timestamp ISO 8601 (UTC-like; here we store as local time for brevity).
    const std::time_t t = std::chrono::system_clock::to_time_t(ev.timestamp);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", std::gmtime(&t));

    sqlite3_bind_text(stmt, 1, buf, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, ev.type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, ev.message.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, ev.where.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE);
}

std::int64_t DB::count_events() const {
    if (!db_) return -1;

    if (!count_stmt_) {
        static const char* csql = "SELECT COUNT(*) FROM ExceptionsLog;";
        if (sqlite3_prepare_v2(db_, csql, -1, &count_stmt_, nullptr) != SQLITE_OK) {
            return -1;
        }
    }

    int rc = sqlite3_step(count_stmt_);
    if (rc != SQLITE_ROW) {
        sqlite3_reset(count_stmt_);
        return -1;
    }
    auto count = sqlite3_column_int64(count_stmt_, 0);
    sqlite3_reset(count_stmt_);
    return count;
}
