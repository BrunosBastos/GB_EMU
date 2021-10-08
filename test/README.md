
## Google Test

### Installation

Install these packages on your machine:
```bash
sudo apt-get install libgtest-dev
sudo apt-get install cmake 
```

Create the necessary library files:
```bash
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make

cd lib
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib
```

On your project test folder, create a file named `CMakeLists.txt` with the following content:
```
cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
```

Then, create a main c++ file named `tests.cpp` with the following startup content:
```cpp
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

### Compilation

After having everything set up, run the following commands on the test root folder to compile and run the tests:
```bash
# creates folder CMakeFiles
cmake CMakeLists.txt

make
./runTests
```

For recompiling, `cmake` is no longer needed.

### Documentation

Github Repository: https://github.com/google/googletest

Documentation on GitHub Pages: https://google.github.io/googletest/