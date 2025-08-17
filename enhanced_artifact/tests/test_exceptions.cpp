#include "Exceptions.h"
#include "BatchProcessor.h"
#include "DB.h"
#include "Logger.h"
#include <cassert>
#include <iostream>
#include <filesystem>

static void test_divide_ok() {
    float r = divide(10.0f, 2.0f);
    assert(r > 4.999f && r < 5.001f);
}

static void test_divide_error() {
    bool threw = false;
    try { (void)divide(1.0f, 0.0f); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw && "divide should throw on zero denominator");
}

static void test_batch_processor() {
    Logger logger;
    std::vector<DivisionTask> tasks = {
        {10.0f, 2.0f},
        {5.0f,  0.0f},   // error
        {9.0f,  3.0f}
    };
    auto results = BatchProcessor::process(tasks, logger);
    assert(results.size() == 3);

    // Check results
    assert(results[0].result.has_value() && std::abs(results[0].result.value() - 5.0f) < 1e-3);
    assert(!results[1].result.has_value() && !results[1].error.empty());
    assert(results[2].result.has_value() && std::abs(results[2].result.value() - 3.0f) < 1e-3);

    // Ensure one exception was logged
    assert(logger.events().size() == 1);
}

static void test_db_logging() {
    // Arrange
    std::filesystem::create_directories("build_artifacts"); // harmless if exists
    DB db("build_artifacts/exceptions.db");
    assert(db.init_schema());

    Logger logger;
    // Simulate two exceptions
    try { throw std::runtime_error("first simulated error"); }
    catch (const std::exception& ex) { logger.log(ex, "test_db_logging"); }

    try { throw std::invalid_argument("second simulated error"); }
    catch (const std::exception& ex) { logger.log(ex, "test_db_logging"); }

    // Act
    auto written = logger.persist_all(db);

    // Assert
    assert(written == 2);
    assert(db.count_events() >= 2);
}

int main() {
    std::cout << "[RUN] unit tests\n";

    test_divide_ok();
    test_divide_error();
    test_batch_processor();
    test_db_logging();

    // SDE demo: show top-level try/catch like original main()
    try {
        do_division();
        do_custom_application_logic();
    } catch (const CustomException& ex) {
        std::cout << "Caught CustomException in tests main: " << ex.what() << "\n";
    } catch (const std::exception& ex) {
        std::cout << "Caught std::exception in tests main: " << ex.what() << "\n";
    } catch (...) {
        std::cout << "Caught unknown exception in tests main.\n";
    }

    std::cout << "[OK] all tests passed\n";
    return 0;
}
