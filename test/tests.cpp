

#include "test_opcodes.cpp"
#include "test_cpu.cpp"
#include "test_mmu.cpp"

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
