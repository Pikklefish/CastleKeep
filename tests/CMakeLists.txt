cmake_minimum_required(VERSION 3.25.0)

set(This CastleTests)

# Source files for the tests
set(Sources
    test_Account.cpp
)

# Create the test executable
add_executable(${This} ${Sources})

# Link the test executable with gtest, Castle, and OpenSSL libraries
target_link_libraries(${This} PUBLIC
    gtest_main
    Castle
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Add test case to be run with CTest
add_test(
    NAME ${This}
    COMMAND ${This}
)
