#include "../src/opcodes.cpp"
#include "../src/mmu.cpp"
#include "../src/cpu.cpp"
#include "../src/types.cpp"
#include "../src/mbc.cpp"
#include "../src/cartridge.cpp"
#include <gtest/gtest.h>


Mmu *mmu;
Cpu *cpu;

class OpcodesTest : public ::testing::Environment {
 public:
  ~OpcodesTest() override {}

  // Override this to define how to set up the environment.
  void SetUp() override {
    Cartridge *c = new Cartridge("../roms/tetris.gb");
    mmu = new Mmu(c);
    cpu = new Cpu(mmu);      
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    free(cpu);
    free(mmu);      
  }
};


TEST(OpcodesTest, test_op_01) {
    // LD BC, NN
    cpu->reg_BC.set(0);
    mmu->address[cpu->pc + 1] = 0x30;
    mmu->address[cpu->pc + 2] = 0x20;

    op_01(mmu, cpu);

    ASSERT_EQ(true, cpu->reg_BC.get() == 0x2030);    
}

 
TEST(OpcodesTest, test_op_02) {
    // LC (BC), A
    cpu->reg_BC.set(0x8000);
    mmu->address[cpu->reg_BC.get()] = 0;
    cpu->reg_A = 0x55;

    op_02(mmu, cpu);

    ASSERT_EQ(true, mmu->address[cpu->reg_BC.get()] == 0x55);    
}


TEST(OpcodesTest, test_op_03) {
    // INC BC
    cpu->reg_BC.set(0);

    op_03(mmu, cpu);
    ASSERT_EQ(true, cpu->reg_BC.get() == 1);   

    cpu->reg_BC.set(0xFFFF);
    op_03(mmu, cpu);
    ASSERT_EQ(true, cpu->reg_BC.get() == 0);   

    cpu->reg_BC.set(0xFF); 
    op_03(mmu, cpu);
    ASSERT_EQ(true, cpu->reg_BC.get() == 0x0100);
}

TEST(OpcodesTest, test_op_04) {
    // INC B
    cpu->reg_BC.high(0);
    op_04(mmu, cpu);

    ASSERT_EQ(true, cpu->reg_BC.high() == 1);
    ASSERT_EQ(true, !cpu->get_z_flag());
    ASSERT_EQ(true, !cpu->get_n_flag());
    ASSERT_EQ(true, !cpu->get_h_flag());

    cpu->reg_BC.high(0xFF);
    op_04(mmu, cpu);

    ASSERT_EQ(true, cpu->reg_BC.high() == 0);
    ASSERT_EQ(true, cpu->get_z_flag());
    ASSERT_EQ(true, !cpu->get_n_flag());
    ASSERT_EQ(true, cpu->get_h_flag());
}

TEST(OpcodesTest, test_op_05) {
    // DEC B
    cpu->reg_BC.high(0);
    op_05(mmu, cpu);

    ASSERT_EQ(true, cpu->reg_BC.high() == 0xFF);
    ASSERT_EQ(true, !cpu->get_z_flag());
    ASSERT_EQ(true, cpu->get_n_flag());
    ASSERT_EQ(true, cpu->get_h_flag());

    cpu->reg_BC.high(1);
    op_05(mmu, cpu);

    ASSERT_EQ(true, cpu->reg_BC.high() == 0);
    ASSERT_EQ(true, cpu->get_z_flag());
    ASSERT_EQ(true, cpu->get_n_flag());
    ASSERT_EQ(true, !cpu->get_h_flag());
}

TEST(OpcodesTest, test_op_06) {
    // LD B, N
    const byte n = 0x10;
    cpu->reg_B = 0;
    mmu->address[cpu->pc + 1] = n;

    op_06(mmu, cpu);

    ASSERT_EQ(true, cpu->reg_B == n);    
}


TEST(OpcodesTest, test_op_07) {
    // RLCA

    op_07(mmu, cpu);

    ASSERT_EQ(true, !cpu->get_z_flag());    
}

TEST(OpcodesTest, test_op_08) {
    // LD NN, SP
    cpu->sp = 0x3020;
    mmu->address[cpu->pc + 1] = 0x00;
    mmu->address[cpu->pc + 2] = 0x80;
    op_08(mmu, cpu);

    ASSERT_EQ(true, mmu->address[0x8000] == 0x20);
    ASSERT_EQ(true, mmu->address[0x8001] == 0x30);
}

