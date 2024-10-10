cmake_minimum_required(VERSION 3.25.0)


# Test for Account
add_executable(test_Account test_Account.cpp)
target_link_libraries(test_Account PUBLIC gtest_main Castle OpenSSL::SSL OpenSSL::Crypto ${PostgreSQL_LIBRARY_DIR}/libpq.lib)
add_test(NAME test_Account COMMAND test_Account)

# Test for Security
add_executable(test_Security test_Security.cpp)
target_link_libraries(test_Security PUBLIC gtest_main Castle OpenSSL::SSL OpenSSL::Crypto)
add_test(NAME test_Security COMMAND test_Security)

# Test for Transaction
add_executable(test_Transaction test_Transaction.cpp)
target_link_libraries(test_Transaction PUBLIC gtest_main Castle OpenSSL::SSL OpenSSL::Crypto ${PostgreSQL_LIBRARY_DIR}/libpq.lib)
add_test(NAME test_Transaction COMMAND test_Transaction)

# Test for Database
add_executable(test_Database test_Database.cpp)
target_link_libraries(test_Database PUBLIC gtest_main Castle OpenSSL::SSL OpenSSL::Crypto ${PostgreSQL_LIBRARY_DIR}/libpq.lib)
add_test(NAME test_Database COMMAND test_Database)

