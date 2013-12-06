/* ************************************************************************ */
/*                                                                          */
/* Tester library                                                           */
/* Copyright (C) 2013 Jiří Fatka <ntsfka@gmail.com>                         */
/*                                                                          */
/* The MIT License (MIT)                                                    */
/*                                                                          */
/* Permission is hereby granted, free of charge, to any person obtaining    */
/* a copy of this software and associated documentation files (the          */
/* "Software"), to deal in the Software without restriction, including      */
/* without limitation the rights to use, copy, modify, merge, publish,      */
/* distribute, sublicense, and/or sell copies of the Software, and to       */
/* permit persons to whom the Software is furnished to do so, subject to    */
/* the following conditions:                                                */
/*                                                                          */
/* The above copyright notice and this permission notice shall be included  */
/* in all copies or substantial portions of the Software.                   */
/*                                                                          */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   */
/*                                                                          */
/* ************************************************************************ */

#ifndef TESTER_HPP_
#define TESTER_HPP_

/* ************************************************************************ */
/* INCLUDES                                                                 */
/* ************************************************************************ */

// C++
#include <stdexcept>
#include <vector>
#include <functional>

#if __cplusplus >= 201103L
#include <chrono>
#else
#include <ctime>
#endif

/* ************************************************************************ */
/* MACROS                                                                   */
/* ************************************************************************ */

/**
 * @brief C++11 support.
 */
#if __cplusplus >= 201103L
#define CXX11
#endif

/* ************************************************************************ */

/**
 * @brief noexcept alias for older standards.
 */
#ifndef CXX11
#define noexcept throw()
#endif

/* ************************************************************************ */

/**
 * @brief Converts argument into a string literal.
 *
 * @param expr Expression.
 *
 * @return Expression as a string literal: "expr".
 */
#define STR(expr) # expr

/* ************************************************************************ */

/**
 * @brief Evaluate argument and converts it into a string literal.
 *
 * @param expr Expression.
 *
 * @return Evaluated expression as a string literal.
 */
#define XSTR(expr) STR(expr)

/* ************************************************************************ */

/**
 * @brief Create test function name.
 *
 * @param name Test name.
 *
 * @return Name of the test function.
 */
#define TEST_NAME(name) name ## _test

/* ************************************************************************ */

/**
 * @brief Create test function declaration.
 *
 * @param name Test name.
 *
 * @return Prototype of the test function.
 */
#define TEST(name) void TEST_NAME(name)()

/* ************************************************************************ */

/**
 * @brief Create an expression that calls test.
 *
 * This macro is a shorthand for:
 * @code run_test(TEST_NAME(name), name) @endcode
 *
 * @param name Test name.
 *
 * @return Test calling expression.
 */
#define TEST_RUN(name) ::tester::run_test(TEST_NAME(name), # name)

/* ************************************************************************ */

/**
 * @brief Declare and Run test with given name.
 *
 * @note This macro using function declaration (prototype) together with
 * function calling.
 *
 * @param name Test name.
 *
 * @return Test function declaration and it's calling expression.
 */
#define TEST_DECL_RUN(name) TEST(name); TEST_RUN(name)

/* ************************************************************************ */

/**
 * @brief Test if given expression is true.
 *
 * @param expr Tested expression.
 *
 * @throw assert_error If expression is false. Exception containts information
 *                     about tested expression and it's position.
 */
#define ASSERT(expr) \
    ::tester::test_assert(expr, "(" # expr ") at line " XSTR(__LINE__))

/* ************************************************************************ */

/**
 * @brief Test values equality.
 *
 * @param lhs Left operand.
 * @param rhs Right operand.
 *
 * @return lhs == rhs assertion.
 */
#define ASSERT_EQ(lhs, rhs) \
    ASSERT(lhs == rhs)

/* ************************************************************************ */

/**
 * @brief Test values unequality.
 *
 * @param lhs Left operand.
 * @param rhs Right operand.
 *
 * @return lhs != rhs assertion.
 */
#define ASSERT_NEQ(lhs, rhs) \
    ASSERT(lhs != rhs)

/* ************************************************************************ */

namespace tester {

/* ************************************************************************ */
/* TYPES                                                                    */
/* ************************************************************************ */

/**
 * @brief Type that represents a point in time.
 */
#ifdef CXX11
using time_point = std::chrono::high_resolution_clock::time_point;
#else
typedef std::clock_t time_point;
#endif

/* ************************************************************************ */

/**
 * @brief Callback test function type.
 */
#ifdef CXX11
using test_func = std::function<void()>;
#else
typedef void (*test_func)();
#endif

/* ************************************************************************ */
/* VARIABLES                                                                */
/* ************************************************************************ */

/// Assertion counter.
extern unsigned int assertion_count;

/* ************************************************************************ */

/// Test counter.
extern unsigned int test_count;

/* ************************************************************************ */

/// Error list.
extern std::vector<std::string> errors;

/* ************************************************************************ */

/// Tests start time.
extern time_point start_time;

/* ************************************************************************ */

/// Tests stop time.
extern time_point stop_time;

/* ************************************************************************ */
/* CLASSES                                                                  */
/* ************************************************************************ */

/**
 * @brief Assertion error.
 *
 * This exception type is used for indication the assertion failed.
 */
class assert_error : public std::runtime_error
{

// Public Ctors
public:


    /**
     * @brief Creates an assertion error.
     *
     * @param what Error message.
     */
    explicit assert_error(const std::string& what)
        : std::runtime_error(what)
    {}


    /**
     * @brief Creates an assertion error.
     *
     * @param what Error message.
     */
    explicit assert_error(const char* what)
        : std::runtime_error(what)
    {}

};

/* ************************************************************************ */
/* FUNCTIONS                                                                */
/* ************************************************************************ */

/**
 * @brief Performs a test.
 *
 * Function calls given test function and prints it's call result onto
 * standard output. The output have format where test name is printed and
 * after that is printed the test result (OK or FAIL).
 *
 * Test can be called recursive and function is able to handle that. It's
 * a simple way to group tests.
 *
 * @param test Pointer to test function. It can be lambda under C++11.
 * @param name Test name.
 *
 * @see TEST_RUN
 */
void run_test(test_func test, const std::string& name) noexcept;

/* ************************************************************************ */

/**
 * @brief Performs tests.
 *
 * This function handle the whole testing system and can be used as only one
 * function call in the main function. The function calls sequentialy
 * following functions:
 *
 *  - start()
 *  - tests()
 *  - stop()
 *  - print_results()
 *
 * @param test A function that tests all required tests.
 *
 * @return Tests result. Can be used directly as program exit status.
 */
int run_tests(test_func tests) noexcept;

/* ************************************************************************ */

/**
 * @brief Throws an exception when `res` is false.
 *
 * @param res    Evaluation result.
 * @param errstr Error string in the thrown exception.
 *
 * @throw assert_error If `res` is false.
 */
void test_assert(bool res, const std::string& errstr);

/* ************************************************************************ */

/**
 * @brief Returns current time.
 *
 * @return Current time in undefined units.
 */
time_point get_time();

/* ************************************************************************ */

/**
 * @brief Starts measuring tests run time.
 *
 * Resets statistical variables and error list.
 */
void start();

/* ************************************************************************ */

/**
 * @brief Stops measuring tests run time.
 */
void stop();

/* ************************************************************************ */

/**
 * @brief Prints testing results.
 *
 * Prints testing statistics onto standard output.
 */
void print_results();

/* ************************************************************************ */

}

/* ************************************************************************ */

#endif // TESTER_HPP_
