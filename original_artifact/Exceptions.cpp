// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdexcept>  // For standard exceptions such as std::invalid_argument and std::runtime_error
#include <exception>  // For std::exception

//------------------------------------------------------------------------------
// CustomException class derived from std::exception.
// This class overrides the what() method to return a custom error message.
//------------------------------------------------------------------------------
class CustomException : public std::exception {
public:
    // Override what() to provide a custom error message.
    const char* what() const noexcept override {
        return "Custom exception occurred in custom application logic.";
    }
};

//------------------------------------------------------------------------------
// Function: do_even_more_custom_application_logic
// Description: Demonstrates throwing a standard exception.
//------------------------------------------------------------------------------
bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    // Throw a standard runtime_error exception to simulate an error scenario.
    throw std::runtime_error("Standard exception thrown in do_even_more_custom_application_logic.");
    // If no exception is thrown, the function would return true.
    return true;
}

//------------------------------------------------------------------------------
// Function: do_custom_application_logic
// Description: Wraps the call to do_even_more_custom_application_logic with a try-catch
//              block for std::exception, then continues processing and finally throws
//              a custom exception to be caught in main.
//------------------------------------------------------------------------------
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    // Wrap the call in a try-catch to handle any standard exceptions.
    try {
        // Call the function that will throw a standard exception.
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& ex) {
        // Display an error message along with the exception's what() message.
        std::cout << "Caught std::exception in do_custom_application_logic: " << ex.what() << std::endl;
    }

    // Continue processing after handling the exception.
    std::cout << "Leaving Custom Application Logic." << std::endl;

    // Throw a custom exception derived from std::exception.
    throw CustomException();
}

//------------------------------------------------------------------------------
// Function: divide
// Description: Performs division and checks for division-by-zero.
//              Throws a standard std::invalid_argument exception if denominator is zero.
//------------------------------------------------------------------------------
float divide(float num, float den)
{
    if (den == 0) {
        // Throw an exception if denominator is zero.
        throw std::invalid_argument("divide: Denominator cannot be zero.");
    }
    return (num / den);
}

//------------------------------------------------------------------------------
// Function: do_division
// Description: Calls the divide function and handles ONLY the exception thrown
//              by it using a specific catch block. The function is marked noexcept.
//------------------------------------------------------------------------------
void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    // Wrap the division call in a try-catch block to capture std::invalid_argument.
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& ex) {
        // Handle the specific exception thrown by divide.
        std::cout << "Caught invalid_argument in do_division: " << ex.what() << std::endl;
    }
}

//------------------------------------------------------------------------------
// Function: main
// Description: Wraps the entire main function logic in a try-catch block that catches,
//              in order, custom exceptions, standard exceptions, and any other exceptions.
//------------------------------------------------------------------------------
int main()
{
    try {
        std::cout << "Exceptions Tests!" << std::endl;

        // Test the division logic which handles a divide-by-zero error.
        do_division();

        // Test the custom application logic which will ultimately throw a CustomException.
        do_custom_application_logic();
    }
    // First, catch the custom exception explicitly.
    catch (const CustomException& ex) {
        std::cout << "Caught CustomException in main: " << ex.what() << std::endl;
    }
    // Next, catch any standard exceptions.
    catch (const std::exception& ex) {
        std::cout << "Caught std::exception in main: " << ex.what() << std::endl;
    }
    // Finally, catch any other exceptions that may have been thrown.
    catch (...) {
        std::cout << "Caught an unknown exception in main." << std::endl;
    }

    return 0;
}
