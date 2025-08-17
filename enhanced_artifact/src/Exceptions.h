#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

/**
 * @brief Custom exception for demo purposes.
 */
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred in custom application logic.";
    }
};

/**
 * @brief Throws std::runtime_error to simulate failure.
 * @return true if success (never reached here in this demo).
 */
bool do_even_more_custom_application_logic();

/**
 * @brief Wraps call to do_even_more... and demonstrates catching std::exception
 *        then throws CustomException at the end.
 * @throws CustomException always
 */
void do_custom_application_logic();

/**
 * @brief Safe division with validation.
 * @throws std::invalid_argument if denominator is zero.
 */
float divide(float num, float den);

/**
 * @brief Demo function: calls divide() inside try/catch and prints result.
 *        Kept noexcept to show local handling.
 */
void do_division() noexcept;

#endif // EXCEPTIONS_H
