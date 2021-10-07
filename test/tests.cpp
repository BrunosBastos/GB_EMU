#include "test_opcodes.cpp"
#include <gtest/gtest.h>

 
int main(int argc, char **argv) {
    testing::Environment* const env = testing::AddGlobalTestEnvironment(new OpcodesTest);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
