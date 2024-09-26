# cmake_minimum_required(VERSION 3.25.0)

# set(This Castle)

# project(${This} C CXX)
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# enable_Testing()

# add_subdirectory(googletest)

# include_directories(${CMAKE_SOURCE_DIR}/include)

# set(Headers
#     include/account.hpp
#     include/security.hpp
# )

# set(Sources
#     src/account.cpp
#     src/security.cpp
# )

# add_library(${This} STATIC ${Sources} ${Headers})

# add_subdirectory(tests)


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

# Include OpenSSL directories
include_directories(${OPENSSL_INCLUDE_DIR})

# Your source and header files
set(Headers
    include/account.hpp
    include/security.hpp
)

set(Sources
    src/account.cpp
    src/security.cpp
)

# Create a static library
add_library(${This} STATIC ${Sources} ${Headers})

# Link OpenSSL libraries to your static library
target_link_libraries(${This} PUBLIC OpenSSL::SSL OpenSSL::Crypto)

# Add subdirectory for tests
add_subdirectory(tests)
