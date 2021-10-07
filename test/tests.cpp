

#include "test_opcodes.cpp"
#include "test_cpu.cpp"

#include <gtest/gtest.h>

Cartridge *c = new Cartridge("../roms/tetris.gb");
Mmu *mmu = new Mmu(c);
Cpu *cpu = new Cpu(mmu);

 
int main(int argc, char **argv) {
    testing::Environment* const env = testing::AddGlobalTestEnvironment(new OpcodesTest);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
