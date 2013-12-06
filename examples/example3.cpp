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

/**
 * This example shows how to use library with lambdas.
 *
 * The TEST_DECL_RUN macro declares a test with given name and runs it. It
 * uses the fact the C++ allows declare function inside function.
 */

/* ************************************************************************ */
/* INCLUDES                                                                 */
/* ************************************************************************ */

// Tester library
#include "../tester.hpp"

// C++
#include <thread>

/* ************************************************************************ */
/* FUNCTIONS                                                                */
/* ************************************************************************ */

/**
 * @brief Main function.
 */
int main()
{
    return tester::run_tests([] {
        // Declare and run
        TEST_DECL_RUN(example3);
    });
}

/* ************************************************************************ */

/**
 * @brief Example 3 test
 */
TEST(example3)
{
    ASSERT(true);

    // Wait for 200 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

/* ************************************************************************ */
