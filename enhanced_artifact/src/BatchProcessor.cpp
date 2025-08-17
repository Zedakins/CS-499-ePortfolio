#include "BatchProcessor.h"
#include "Exceptions.h"

std::vector<DivisionResult> BatchProcessor::process(const std::vector<DivisionTask>& tasks, Logger& logger) {
    std::vector<DivisionResult> out;
    out.reserve(tasks.size());  // O(n) auxiliary memory, avoids reallocations.

    for (const auto& t : tasks) {
        DivisionResult r;
        r.num = t.num;
        r.den = t.den;
        try {
            if (t.den == 0.0f) {
                // Reuse validated function to ensure consistent behavior.
                throw std::invalid_argument("divide: Denominator cannot be zero.");
            }
            r.result = t.num / t.den;
        } catch (const std::exception& ex) {
            r.error = ex.what();
            logger.log(ex, "BatchProcessor::process");
        }
        out.push_back(std::move(r));
    }
    return out;
}
