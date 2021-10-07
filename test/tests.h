#ifndef TESTS_H
#define TESTS_H

#include <gtest/gtest.h>

#include "../src/cartridge.cpp"
#include "../src/mmu.cpp"
#include "../src/cpu.cpp"
#include "../src/mbc.cpp"
#include "../src/opcodes.cpp"
#include "../src/types.cpp"


extern Mmu *mmu;
extern Cpu *cpu;

#endif
