cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Ensure threads are found
find_package(Threads REQUIRED)

# Link runTests with what we want to test, the GTest, and pthread library
add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} Threads::Threads)