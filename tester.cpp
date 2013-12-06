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

/* ************************************************************************ */
/* INCLUDES                                                                 */
/* ************************************************************************ */

// Declaration
#include "tester.hpp"

// C++
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <iomanip>

/* ************************************************************************ */

namespace tester {

/* ************************************************************************ */
/* VARIABLES                                                                */
/* ************************************************************************ */

///Assertion counter.
unsigned int assertion_count;

/* ************************************************************************ */

/// Test counter.
unsigned int test_count;

/* ************************************************************************ */

/// Error list.
std::vector<std::string> errors;

/* ************************************************************************ */

/// Tests start time.
time_point start_time;

/* ************************************************************************ */

/// Tests stop time.
time_point stop_time;

/* ************************************************************************ */

/// Test call depth.
static unsigned int depth;

/* ************************************************************************ */
/* FUNCTIONS                                                                */
/* ************************************************************************ */

void run_test(test_func test, const std::string& name) noexcept
{
    test_count++;

    for (size_t i = 0; i < depth; ++i)
        std::cout << "  ";

    // Print test name
    std::cout << name;

    const size_t space = 50 - name.length() - depth * 2;
    for (size_t i = 0; i < space; ++i)
        std::cout << " ";

    // Backup output buffer
    std::streambuf* old = std::cout.rdbuf();
    std::stringbuf strbuf;
    std::cout.rdbuf(&strbuf);

    // Increase depth
    depth++;

    const size_t err_cnt = errors.size();

    try
    {
        // Call test
        test();
    }
    catch (const assert_error& e)
    {
        errors.push_back(name + ": " + std::string(e.what()));
    }
    catch (const std::exception& e)
    {
        errors.push_back("Uncaught exception of type "
            "'" + std::string(typeid(e).name()) + "' with error: " +
            std::string(e.what()));
    }
    catch (...)
    {
        errors.push_back("Unknown exception type caught");
    }

    // Decrease depth
    depth--;

    // Reset buffer
    std::cout.rdbuf(old);

    if (err_cnt == errors.size())
        std::cout << "OK";
    else
        std::cout << "FAIL";

    std::cout << "\n";

    // Print childs output
    std::cout << strbuf.str();

    // Flush buffer
    std::cout.flush();
}

/* ************************************************************************ */

int run_tests(test_func tests) noexcept
{
    // Start tests
    start();

    // Call tests function
    tests();

    // Stop tests
    stop();

    // Print results
    print_results();

    return errors.empty() ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* ************************************************************************ */

void test_assert(bool res, const std::string& errstr)
{
    if (res)
        assertion_count++;
    else
        throw assert_error(errstr);
}

/* ************************************************************************ */

time_point get_time()
{
#ifdef CXX11
    return std::chrono::high_resolution_clock::now();
#else
    return clock();
#endif
}

/* ************************************************************************ */

void start()
{
    assertion_count = 0;
    depth = 0;
    errors.clear();
    test_count = 0;
    start_time = get_time();
    stop_time = time_point();
}

/* ************************************************************************ */

void stop()
{
    stop_time = get_time();
}

/* ************************************************************************ */

void print_results()
{
#ifdef CXX11
    auto diff = stop_time - start_time;
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
#else
    clock_t passed = 1000.0 * (stop_time - start_time) / CLOCKS_PER_SEC;
#endif

    // Print test results
    std::cout << "\n";
    std::cout << "Time      : " << passed << " ms\n";
    std::cout << "Tests     : " << (test_count - errors.size()) << "/" << test_count << "\n";
    std::cout << "Assertions: " << assertion_count << "\n\n";

    // Some errors found
    if (!errors.empty())
    {
        std::cerr << "Errors: \n";

        // Print assertion errors
#ifdef CXX11
        for (const auto& error : errors)
            std::cerr << "  " << error << "\n";
#else
        // How I like for-range loops
        for (std::vector<std::string>::const_iterator it = errors.begin(),
            ite = errors.end(); it != ite; ++it)
        {
            std::cerr << "  " << *it << "\n";
        }
#endif

        std::cerr << "\n";
    }
    else
    {
        std::cout << "No errors\n\n";
        std::cout.flush();
    }
}

/* ************************************************************************ */

}

/* ************************************************************************ */
