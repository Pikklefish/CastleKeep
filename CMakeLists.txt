cmake_minimum_required(VERSION 3.25.0)

set(This Castle)

project(${This} C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Enable testing
enable_testing()

# Add GoogleTest subdirectory
add_subdirectory(googletest)

# Include directory for your headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find OpenSSL package (make sure OpenSSL is installed and the path is correct)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Set PostgreSQL directories
set(PostgreSQL_INCLUDE_DIR "C:/Program Files/PostgreSQL/17/include")
set(PostgreSQL_LIBRARY_DIR "C:/Program Files/PostgreSQL/17/lib")

# Include PostgreSQL headers
include_directories(${PostgreSQL_INCLUDE_DIR})

# Your source and header files
set(Headers
    include/account.hpp
    include/security.hpp
    include/transaction.hpp
    include/auditLog.hpp
    include/database.hpp
)

set(Sources
    src/account.cpp
    src/security.cpp
    src/transaction.cpp
    src/auditLog.cpp
    src/Database.cpp
)

# Create a static library
add_library(${This} STATIC ${Sources} ${Headers})

# Link OpenSSL and MySQL Connector libraries to your static library
target_link_libraries(${This} PUBLIC OpenSSL::SSL OpenSSL::Crypto ${PostgreSQL_LIBRARY_DIR}/libpq.lib)

# Add subdirectory for tests
add_subdirectory(tests)

