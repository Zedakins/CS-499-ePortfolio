#include "Exceptions.h"
#include "Logger.h"
#include <iostream>

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic.\n";
    throw std::runtime_error("Standard exception thrown in do_even_more_custom_application_logic.");
    // return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic.\n";
    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded.\n";
        }
    } catch (const std::exception& ex) {
        std::cout << "Caught std::exception in do_custom_application_logic: " << ex.what() << "\n";
        // Optional: log through a global/singleton if you wire one. For demo, just continue.
    }

    std::cout << "Leaving Custom Application Logic.\n";
    throw CustomException();
}

float divide(float num, float den)
{
    if (den == 0.0f) {
        throw std::invalid_argument("divide: Denominator cannot be zero.");
    }
    return num / den;
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0.0f;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << "\n";
    } catch (const std::invalid_argument& ex) {
        std::cout << "Caught invalid_argument in do_division: " << ex.what() << "\n";
    }
}
