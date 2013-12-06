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
 * Basic example how to write a simple test and check values.
 */

/* ************************************************************************ */
/* INCLUDES                                                                 */
/* ************************************************************************ */

// Tester library
#include "../tester.hpp"

/* ************************************************************************ */
/* FUNCTIONS                                                                */
/* ************************************************************************ */

/**
 * @brief Example 1 test
 */
TEST(example1)
{
    int a = 10;

    ASSERT(a == 10);
    ASSERT_EQ(a, 10);
    ASSERT_NEQ(a, 11);
}

/* ************************************************************************ */

void tests_run()
{
    TEST_RUN(example1);
}

/* ************************************************************************ */

/**
 * @brief Main function.
 */
int main()
{
    return tester::run_tests(tests_run);
}

/* ************************************************************************ */
