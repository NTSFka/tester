# ######################################################################### #
#                                                                           #
# Tester library                                                            #
# Copyright (C) 2013 Jiří Fatka <ntsfka@gmail.com>                          #
#                                                                           #
# The MIT License (MIT)                                                     #
#                                                                           #
# Permission is hereby granted, free of charge, to any person obtaining     #
# a copy of this software and associated documentation files (the           #
# "Software"), to deal in the Software without restriction, including       #
# without limitation the rights to use, copy, modify, merge, publish,       #
# distribute, sublicense, and/or sell copies of the Software, and to        #
# permit persons to whom the Software is furnished to do so, subject to     #
# the following conditions:                                                 #
#                                                                           #
# The above copyright notice and this permission notice shall be included   #
# in all copies or substantial portions of the Software.                    #
#                                                                           #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   #
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                #
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.    #
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY      #
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,      #
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE         #
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                    #
#                                                                           #
# ######################################################################### #

cmake_minimum_required(VERSION 2.6.2)

# Create project
project(tester)

# C++11 is disabled by default
set(ENABLE_CXX11 FALSE)

# Only if CXX11 variable is set to True the C++11 support is enabled
if (CXX11)
    message("-- C++11 enabled")
    set(ENABLE_CXX11 TRUE)
endif (CXX11)
unset(CXX11 CACHE)

# Create library
add_library(tester tester.hpp tester.cpp)

if (ENABLE_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (ENABLE_CXX11)

# ######################################################################### #
# TESTING                                                                   #
# ######################################################################### #

# Testing examples
enable_testing()

# Simple usage example
add_test(example1 example1)
add_executable(example1 examples/example1.cpp)
target_link_libraries(example1 tester)

# Child tests example
add_test(example2 example2)
add_executable(example2 examples/example2.cpp)
target_link_libraries(example2 tester)

# C++11 lambda example
if (ENABLE_CXX11)
    # This test shows usage of lambdas that are available in C++11
    add_test(example3 example3)
    add_executable(example3 examples/example3.cpp)
    target_link_libraries(example3 tester)
endif (ENABLE_CXX11)

# Splitting into multiple source files example
add_test(example4 example4)
add_executable(example4 examples/example4.cpp examples/example4.1.cpp examples/example4.2.cpp)
target_link_libraries(example4 tester)

# ######################################################################### #
