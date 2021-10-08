#include "tests.h"


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
        free(mmu);
        free(cpu);
    }
};

TEST(OpcodesTest, test_op_01) {
    // LD BC, NN
    cpu->reg_BC.set(0);
    mmu->address[cpu->pc + 1] = 0x30;
    mmu->address[cpu->pc + 2] = 0x20;

    op_01(mmu, cpu);

    ASSERT_TRUE(cpu->reg_BC.get() == 0x2030);
};

TEST(OpcodesTest, test_op_02) {
    // LC (BC), A
    cpu->reg_BC.set(0x8000);
    mmu->address[cpu->reg_BC.get()] = 0;
    cpu->reg_A = 0x55;

    op_02(mmu, cpu);

    ASSERT_TRUE(mmu->address[cpu->reg_BC.get()] == 0x55);
};

TEST(OpcodesTest, test_op_03) {
    // INC BC
    cpu->reg_BC.set(0);

    op_03(mmu, cpu);
    ASSERT_TRUE(cpu->reg_BC.get() == 1);

    cpu->reg_BC.set(0xFFFF);
    op_03(mmu, cpu);
    ASSERT_TRUE(cpu->reg_BC.get() == 0);

    cpu->reg_BC.set(0xFF);
    op_03(mmu, cpu);
    ASSERT_TRUE(cpu->reg_BC.get() == 0x0100);
};

TEST(OpcodesTest, test_op_06) {
    // LD B, N
    const byte n = 0x10;
    cpu->reg_B = 0;
    mmu->address[cpu->pc + 1] = n;

    op_06(mmu, cpu);

    ASSERT_TRUE(cpu->reg_B == n);
};

TEST(OpcodesTest, test_op_07) {
    // RLCA

    op_07(mmu, cpu);

    ASSERT_TRUE(!cpu->get_z_flag());
};

TEST(OpcodesTest, test_op_08) {
    // LD NN, SP
    cpu->sp = 0x3020;
    mmu->address[cpu->pc + 1] = 0x00;
    mmu->address[cpu->pc + 2] = 0x80;
    op_08(mmu, cpu);

    ASSERT_TRUE(mmu->address[0x8000] == 0x20);
    ASSERT_TRUE(mmu->address[0x8001] == 0x30);
};

TEST(OpcodesTest, test_op_0A) {
    // LD A, (BC)
    cpu->reg_A = 0;
    cpu->reg_BC.set(0x8000);
    mmu->address[cpu->reg_BC.get()] = 0x20;

    op_0A(mmu, cpu);

    ASSERT_TRUE(cpu->reg_A == 0x20);
};

TEST(OpcodesTest, test_op_0B) {
    // DEC BC
    cpu->reg_BC.set(0);

    op_0B(mmu, cpu);
    ASSERT_TRUE(cpu->reg_BC.get() == 0xFFFF);

    cpu->reg_BC.set(0x0100);
    op_0B(mmu, cpu);
    ASSERT_TRUE(cpu->reg_BC.get() == 0xFF);
};

TEST(OpcodesTest, test_op_0E) {
    // LD C, N
    mmu->address[cpu->pc + 1] = 0x23;
    cpu->reg_C = 0;

    op_0E(mmu, cpu);
    ASSERT_TRUE(cpu->reg_C == 0x23);
};


TEST(OpcodesTest, test_op_0F) {
    // RRCA
    op_F0(mmu, cpu);

    ASSERT_TRUE(!cpu->get_z_flag());
};


TEST(OpcodesTest, test_op_11) {
    // LD DE, NN
    mmu->address[cpu->pc + 1] = 0x25;
    mmu->address[cpu->pc + 2] = 0x32;
    cpu->reg_DE.set(0);

    op_11(mmu, cpu);

    ASSERT_TRUE(cpu->reg_DE.get() == 0x3225);
};


TEST(OpcodesTest, test_op_12) {
    // LD (DE), A
    cpu->reg_DE.set(0x8000);
    cpu->reg_A = 0x10;
    op_12(mmu, cpu);

    ASSERT_TRUE(mmu->address[cpu->reg_DE.get()] == cpu->reg_A);
};


TEST(OpcodesTest, test_op_13) {
    // INC DE 
    cpu->reg_DE.set(0);
    op_13(mmu, cpu);
    ASSERT_TRUE(cpu->reg_DE.get() == 1);

    cpu->reg_DE.set(0xFF);
    op_13(mmu, cpu);
    ASSERT_TRUE(cpu->reg_DE.get() == 0x0100);

    cpu->reg_DE.set(0xFFFF);
    op_13(mmu, cpu);
    ASSERT_TRUE(cpu->reg_DE.get() == 0);

};

TEST(OpcodesTest, test_op_16) {
    // LD D, N
    cpu->reg_D = 0;
    mmu->address[cpu->pc + 1] = 0x20;
    op_16(mmu, cpu);
    ASSERT_TRUE(cpu->reg_D == 0x20);
};

TEST(OpcodesTest, test_op_17) {
    // RLCA
    op_17(mmu, cpu);
    ASSERT_TRUE(!cpu->get_z_flag());
};

TEST(OpcodesTest, test_op_18) {
    // JR NN
    int pc = cpu->pc;
    mmu->address[cpu->pc + 1] = 0x10;
    op_18(mmu, cpu);

    ASSERT_TRUE(cpu->pc == pc + (char)0x10 + 1);

    pc = cpu->pc;
    mmu->address[cpu->pc + 1] = 0xFF;
    ASSERT_TRUE(cpu->pc == pc);
};

TEST(OpcodesTest, test_op_1A) {
    // ADD (DE), A
    cpu->reg_DE.set(0x8000);
    cpu->reg_A = 0xF0;
    op_1A(mmu, cpu);
    
    ASSERT_TRUE(mmu->address[cpu->reg_DE.get()] == cpu->reg_A);
};

TEST(OpcodesTest, test_op_1B) {
    // DEC DE
    cpu->reg_DE.set(0x8000);
    op_1B(mmu, cpu);
    ASSERT_TRUE(cpu->reg_DE.get() == 0x7FFF);

    cpu->reg_DE.set(0);
    op_1B(mmu, cpu);
    ASSERT_TRUE(cpu->reg_DE.get() == 0xFFFF);
};

TEST(OpcodesTest, test_op_1E) {
    // LD E, N
    cpu->reg_E = 0;
    mmu->address[cpu->pc + 1] = 0x20; 
    op_1E(mmu, cpu);
    ASSERT_TRUE(cpu->reg_E == 0x20);
};

TEST(OpcodesTest, test_op_1F) {
    // RRA
    cpu->set_z_flag(1);
    op_1F(mmu, cpu);
    ASSERT_TRUE(!cpu->get_z_flag());
};

TEST(OpcodesTest, test_op_20) {
    // JR NZ, NN
    int pc = cpu->pc;
    mmu->address[cpu->pc + 1] = 0x01;
    cpu->set_z_flag(0);
    op_20(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + char(0x01) + 1);

    pc = cpu->pc;
    mmu->address[cpu->pc + 1] = 0xFF;
    op_20(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + char(0xFF) + 1);

    cpu->set_z_flag(1);
    pc = cpu->pc;
    op_20(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + 1);
};

TEST(OpcodesTest, test_op_21) {
    // LD HL, NN
    cpu->reg_HL.set(0);
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x30;
    op_21(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x3020);
};

TEST(OpcodesTest, test_op_22) {
    // LDI (HL), A
    cpu->reg_HL.set(0x8000);
    cpu->reg_A = 0x45;
    op_22(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x8001);
    ASSERT_TRUE(mmu->address[0x8000] == cpu->reg_A);

    cpu->reg_HL.set(0xFFFF);
    cpu->reg_A = 0x45;
    op_22(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0);
    ASSERT_TRUE(mmu->address[0xFFFF] == cpu->reg_A);
};

TEST(OpcodesTest, test_op_23) {
    // INC HL
    cpu->reg_HL.set(0x8000);
    op_23(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x8001);

    cpu->reg_HL.set(0xFFFF);
    op_23(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0);

};

TEST(OpcodesTest, test_op_26) {
    // LD H, N
    mmu->address[cpu->pc + 1] = 0x20;
    cpu->reg_H = 0;
    op_26(mmu, cpu);
    ASSERT_TRUE(cpu->reg_H == 0x20);
};

TEST(OpcodesTest, test_op_27) {
    // DAA TODO:
    ASSERT_TRUE(true);
};

TEST(OpcodesTest, test_op_28) {
    // JR Z, N
    cpu->set_z_flag(0);
    int pc = cpu->pc;
    op_28(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + 1);

    cpu->set_z_flag(1);
    mmu->address[cpu->pc + 1] = 0x20;
    pc = cpu->pc;
    op_28(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + (char)0x20 + 1);

    mmu->address[cpu->pc + 1] = 0xFF;
    pc = cpu->pc;
    op_28(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + (char)0xFF + 1);
};

TEST(OpcodesTest, test_op_2A) {
    // LDI A, (HL)
    cpu->reg_HL.set(0x8000);
    cpu->reg_A = 0;
    mmu->address[cpu->reg_HL.get()] = 0x20;
    op_2A(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x8001);
    ASSERT_TRUE(cpu->reg_A == 0x20);
};

TEST(OpcodesTest, test_op_2B) {
    // DEC HL
    cpu->reg_HL.set(0x8000);
    op_2B(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x7FFF);

    cpu->reg_HL.set(0);
    op_2B(mmu, cpu);
    ASSERT_TRUE(cpu->reg_HL.get() == 0xFFFF);
};

TEST(OpcodesTest, test_op_2E) {
    // LD L, N
    mmu->address[cpu->pc + 1] = 0x20;
    cpu->reg_L = 0;
    op_2E(mmu, cpu);
    ASSERT_TRUE(cpu->reg_L == 0x20);
};

TEST(OpcodesTest, test_op_2F) {
    // CPL
    cpu->set_n_flag(0);
    cpu->set_h_flag(0);
    cpu->reg_A = 0;
    op_2F(mmu, cpu);
    ASSERT_TRUE(cpu->reg_A == 0xFF);
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());

    cpu->reg_A = 0xF0;
    op_2F(mmu, cpu);
    ASSERT_TRUE(cpu->reg_A == 0x0F);
};

TEST(OpcodesTest, test_op_30) {
    // JR NC, N
    cpu->set_c_flag(1);
    int pc = cpu->pc;
    op_30(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + 1);

    cpu->set_c_flag(0);
    mmu->address[cpu->pc + 1] = 0x20;
    pc = cpu->pc;
    op_30(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + (char)0x20 + 1);

    mmu->address[cpu->pc + 1] = 0xFF;
    pc = cpu->pc;
    op_30(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + (char)0xFF + 1);
};

TEST(OpcodesTest, test_op_31) {
    // LD SP, NN
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x30;
    cpu->sp = 0;
    op_31(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x3020);
};

TEST(OpcodesTest, test_op_32) {
    // LDD (HL), A
    cpu->reg_HL.set(0x8000);
    cpu->reg_A = 0x10;
    op_32(mmu, cpu);
    ASSERT_TRUE(mmu->address[0x8000] == 0x10);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x7FFF);
};

TEST(OpcodesTest, test_op_33) {
    // INC SP
    cpu->sp = 0;
    op_33(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 1);

    cpu->sp = 0xFFFF;
    op_33(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0);
};

TEST(OpcodesTest, test_op_34) {
    // INC (HL)
    cpu->reg_HL.set(0x8000);
    mmu->address[cpu->reg_HL.get()] = 0;
    op_34(mmu, cpu);
    ASSERT_TRUE(mmu->address[cpu->reg_HL.get()] == 1);

    mmu->address[cpu->reg_HL.get()] = 0xFF;
    op_34(mmu, cpu);
    ASSERT_TRUE(mmu->address[cpu->reg_HL.get()] == 0);
};

TEST(OpcodesTest, test_op_35) {
    // DEC (HL)
    cpu->reg_HL.set(0x8000);
    mmu->address[cpu->reg_HL.get()] = 0;
    op_35(mmu, cpu);
    ASSERT_TRUE(mmu->address[cpu->reg_HL.get()] == 0xFF);

    mmu->address[cpu->reg_HL.get()] = 0xFF;
    op_35(mmu, cpu);
    ASSERT_TRUE(mmu->address[cpu->reg_HL.get()] == 0xFE);
};

TEST(OpcodesTest, test_op_36) {
    // LD (HL), N
    cpu->reg_HL.set(0x8000);
    mmu->address[cpu->reg_HL.get()] = 0;
    mmu->address[cpu->pc + 1 ] = 10;
    op_36(mmu, cpu);
    ASSERT_TRUE(mmu->address[cpu->reg_HL.get()] == 10);
};

TEST(OpcodesTest, test_op_37) {
    // SCF
    cpu->set_n_flag(1);
    cpu->set_h_flag(1);
    cpu->set_c_flag(0);
    op_37(mmu, cpu);
    ASSERT_TRUE(cpu->get_c_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
};

TEST(OpcodesTest, test_op_38) {
    // JR C, N
    cpu->set_c_flag(0);
    int pc = cpu->pc;
    op_38(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + 1);

    cpu->set_c_flag(1);
    mmu->address[cpu->pc + 1] = 0x20;
    pc = cpu->pc;
    op_38(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + (char)0x20 + 1);

    mmu->address[cpu->pc + 1] = 0xFF;
    pc = cpu->pc;
    op_38(mmu, cpu);
    ASSERT_TRUE(cpu->pc == pc + (char)0xFF + 1);
};

TEST(OpcodesTest, test_op_3A) {
    // LDD A, (HL)
    cpu->reg_HL.set(0x8000);
    mmu->address[cpu->reg_HL.get()] = 0x10;
    cpu->reg_A = 0;
    op_3A(mmu, cpu);
    ASSERT_TRUE(cpu->reg_A == 0x10);
    ASSERT_TRUE(cpu->reg_HL.get() == 0x7FFF);
};

TEST(OpcodesTest, test_op_3B) {
    // DEC SP
    cpu->sp = 0;
    op_3B(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0xFFFF);

    cpu->sp = 1;
    op_3B(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0);
};

TEST(OpcodesTest, test_op_3E) {
    // LD A, N
    mmu->address[cpu->pc + 1] = 0x10;
    cpu->reg_A = 0;
    op_3E(mmu, cpu);
    ASSERT_TRUE(cpu->reg_A == 0x10);
};

TEST(OpcodesTest, test_op_3F) {
    // CCF
    cpu->set_n_flag(1);
    cpu->set_h_flag(1);
    cpu->set_c_flag(0);
    op_3F(mmu, cpu);
    ASSERT_TRUE(cpu->get_c_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());

    cpu->set_c_flag(1);
    op_3F(mmu, cpu);
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(OpcodesTest, test_op_C0) {
    // RET NZ
    cpu->set_z_flag(0);
    cpu->sp = 0x10;
    cpu->pc = 0;
    mmu->address[cpu->sp] = 0x00;
    mmu->address[cpu->sp + 1] = 0x01;
    op_C0(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);

    cpu->set_z_flag(1);
    op_C0(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);
};

TEST(OpcodesTest, test_op_C2) {
    // JP NZ
    cpu->set_z_flag(0);
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_C2(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);

    cpu->set_z_flag(1);
    cpu->pc = 0x100;
    op_C2(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
};

TEST(OpcodesTest, test_op_C3) {
    // JP NN
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_C3(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);
};

TEST(OpcodesTest, test_op_C4) {
    // CALL NZ, NN
    cpu->set_z_flag(0);
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_C4(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);
    ASSERT_TRUE(cpu->sp == 0xFFFF - 2);
    ASSERT_TRUE(mmu->address[cpu->sp] == 0x03);
    ASSERT_TRUE(mmu->address[cpu->sp + 1] == 0x01);

    cpu->set_z_flag(1);
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_C4(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
    ASSERT_TRUE(cpu->sp == 0xFFFF);
};

TEST(OpcodesTest, test_op_C7) {
    // RST 00
    cpu->pc = 0x100;
    op_C7(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0xFFFF);
};

TEST(OpcodesTest, test_op_C8) {
    // RET Z
    cpu->set_z_flag(1);
    cpu->sp = 0x10;
    cpu->pc = 0;
    mmu->address[cpu->sp] = 0x00;
    mmu->address[cpu->sp + 1] = 0x01;
    op_C8(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);

    cpu->set_z_flag(0);
    op_C8(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);
};

TEST(OpcodesTest, test_op_CA) {
    // JP Z, NN
    cpu->set_z_flag(1);
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_CA(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);

    cpu->set_z_flag(0);
    cpu->pc = 0x100;
    op_CA(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
};

TEST(OpcodesTest, test_op_CC) {
    // CALL Z, NN
    cpu->set_z_flag(1);
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_CC(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);
    ASSERT_TRUE(cpu->sp == 0xFFFF - 2);
    ASSERT_TRUE(mmu->address[cpu->sp] == 0x03);
    ASSERT_TRUE(mmu->address[cpu->sp + 1] == 0x01);

    cpu->set_z_flag(0);
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_CC(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
    ASSERT_TRUE(cpu->sp == 0xFFFF);
};

TEST(OpcodesTest, test_op_CD) {
    // CALL NN
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_CD(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);
    ASSERT_TRUE(cpu->sp == 0xFFFF - 2);
    ASSERT_TRUE(mmu->address[cpu->sp] == 0x03);
    ASSERT_TRUE(mmu->address[cpu->sp + 1] == 0x01);
};

TEST(OpcodesTest, test_op_CF) {
    // RST 08
    cpu->pc = 0x100;
    op_CF(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x07);
};

TEST(OpcodesTest, test_op_D0) {
    // RET NZ
    cpu->set_c_flag(0);
    cpu->sp = 0x10;
    cpu->pc = 0;
    mmu->address[cpu->sp] = 0x00;
    mmu->address[cpu->sp + 1] = 0x01;
    op_D0(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);

    cpu->set_c_flag(1);
    op_D0(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);
};

TEST(OpcodesTest, test_op_D2) {
    // JP NC
    cpu->set_c_flag(0);
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_D2(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);

    cpu->set_c_flag(1);
    cpu->pc = 0x100;
    op_D2(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
};

TEST(OpcodesTest, test_op_D4) {
    // CALL NC, NN
    cpu->set_c_flag(0);
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_D4(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);
    ASSERT_TRUE(cpu->sp == 0xFFFF - 2);
    ASSERT_TRUE(mmu->address[cpu->sp] == 0x03);
    ASSERT_TRUE(mmu->address[cpu->sp + 1] == 0x01);

    cpu->set_c_flag(1);
    cpu->sp = 0xFFFF;
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_D4(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
    ASSERT_TRUE(cpu->sp == 0xFFFF);
};

TEST(OpcodesTest, test_op_D7) {
    // RST 10
    cpu->pc = 0x100;
    op_D7(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x0F);
};

TEST(OpcodesTest, test_op_D8) {
    // RET C
    cpu->set_c_flag(1);
    cpu->sp = 0x10;
    cpu->pc = 0;
    mmu->address[cpu->sp] = 0x00;
    mmu->address[cpu->sp + 1] = 0x01;
    op_D8(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);

    cpu->set_c_flag(0);
    op_D8(mmu, cpu);
    ASSERT_TRUE(cpu->sp == 0x12);
    ASSERT_TRUE(cpu->pc == 0xFF);
};

TEST(OpcodesTest, test_op_DA) {
    // JP C
    cpu->set_c_flag(1);
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[cpu->pc + 2] = 0x10;
    op_DA(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x1020 - 1);

    cpu->set_c_flag(0);
    cpu->pc = 0x100;
    op_DA(mmu, cpu);
    ASSERT_TRUE(cpu->pc == 0x102);
};

TEST(OpcodesTest, test_op_DF) {
    // RST 18
    cpu->pc = 0x100;
    op_DF(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x17);
};

TEST(OpcodesTest, test_op_E0) {
    // LDH A
    cpu->pc = 0x100;
    cpu->reg_A = 0x20;
    mmu->address[cpu->pc + 1] = 0x10;
    mmu->address[0xff00 + 0x10] = 0;
    op_E0(mmu, cpu);
    ASSERT_EQ(mmu->address[0xff10], 0x20);
};

TEST(OpcodesTest, test_op_E2) {
    // LD (C), A
    cpu->pc = 0x100;
    cpu->reg_A = 0x20;
    cpu->reg_C = 0x10;
    mmu->address[cpu->pc + 1] = 0x10;
    mmu->address[0xff00 + cpu->reg_C] = 0;
    op_E2(mmu, cpu);
    ASSERT_EQ(mmu->address[0xff00 + cpu->reg_C], 0x20);
};

TEST(OpcodesTest, test_op_E7) {
    // RST 20
    cpu->pc = 0x100;
    op_E7(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x1F);
};

TEST(OpcodesTest, test_op_E8) {
    // ADD SP, N TODO: more tests for this opcode
    cpu->pc = 0x100;
    mmu->address[cpu->pc + 1] = 0;
    cpu->sp = 0xFFFE;
    op_E8(mmu, cpu);
    ASSERT_EQ(cpu->sp, 0xFFFE);
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    mmu->address[cpu->pc + 1] = 0xFF;
    cpu->sp = 0xFFFE;
    op_E8(mmu, cpu);
    ASSERT_EQ(cpu->sp, 0xFFFD);
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(OpcodesTest, test_op_E9) {
    // JP HL
    cpu->pc = 0x100;
    cpu->reg_HL.set(0x8000);
    op_E9(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x8000 - 1);
};

TEST(OpcodesTest, test_op_EA) {
    // LD (NN), A
    cpu->pc = 0x100;
    cpu->reg_A = 0x20;
    mmu->address[cpu->pc + 1] = 0x01;
    mmu->address[cpu->pc + 2] = 0x80;
    op_EA(mmu, cpu);
    ASSERT_EQ(mmu->address[0x8001], 0x20);
};

TEST(OpcodesTest, test_op_EF) {
    // RST 28
    cpu->pc = 0x100;
    op_EF(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x27);
};

TEST(OpcodesTest, test_op_F0) {
    // LD A, (N)
    cpu->pc = 0x100;
    cpu->reg_A = 0;
    mmu->address[cpu->pc + 1] = 0x20;
    mmu->address[0xff00 + 0x20] = 0x30;
    op_F0(mmu, cpu);
    ASSERT_EQ(cpu->reg_A, 0x30);
};


TEST(OpcodesTest, test_op_F2) {
    // LD A, (C)
    cpu->pc = 0x100;
    cpu->reg_A = 0;
    cpu->reg_C = 0x20;
    mmu->address[0xff00 + 0x20] = 0x30;
    op_F2(mmu, cpu);
    ASSERT_EQ(cpu->reg_A, 0x30);
};

TEST(OpcodesTest, test_op_F7) {
    // RST 30
    cpu->pc = 0x100;
    op_F7(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x2F);
};

// TODO: F8

TEST(OpcodesTest, test_op_F9) {
    // LD SP, HL
    cpu->sp = 0;
    cpu->reg_HL.set(0x8000);
    op_F9(mmu, cpu);
    ASSERT_EQ(cpu->sp, 0x8000);
};

TEST(OpcodesTest, test_op_FA) {
    // LD A, (NN)
    cpu->pc = 0x100;
    cpu->reg_A = 0;
    mmu->address[cpu->pc + 1] = 0x01;
    mmu->address[cpu->pc + 2] = 0x80;
    mmu->address[0x8001] = 0x30;
    op_FA(mmu, cpu);
    ASSERT_EQ(cpu->reg_A, 0x30);
};

TEST(OpcodesTest, test_op_FF) {
    // RST 38
    cpu->pc = 0x100;
    op_FF(mmu, cpu);
    ASSERT_EQ(cpu->pc, 0x37);
};

