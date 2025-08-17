#ifndef BATCH_PROCESSOR_H
#define BATCH_PROCESSOR_H

#include "Logger.h"
#include <vector>
#include <optional>

/**
 * @brief Simple task representing a division operation.
 */
struct DivisionTask {
    float num{};
    float den{};
};

/**
 * @brief Result of a division task. If error occurs, result is nullopt and error contains info.
 */
struct DivisionResult {
    float num{};
    float den{};
    std::optional<float> result;
    std::string error;
};

/**
 * @brief Algorithms & Data Structures: single-pass (O(n)) batch processing of division tasks,
 *        capturing results and logging exceptions via injected Logger.
 */
class BatchProcessor {
public:
    static std::vector<DivisionResult> process(const std::vector<DivisionTask>& tasks, Logger& logger);
};

#endif // BATCH_PROCESSOR_H
