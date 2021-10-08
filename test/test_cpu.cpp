#include "tests.h"


class CpuTest : public ::testing::Environment {
 public:
  ~CpuTest() override {}

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


TEST(CpuTest, test_swap8) {
    cpu->reg_B = 0x12;
    cpu->swap8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x21);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->swap8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_swap16) {
    cpu->reg_BC.set(0x1234);
    cpu->swap16(&cpu->reg_BC);

    ASSERT_EQ(cpu->reg_BC.get(), 0x3412);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0);
    cpu->swap16(&cpu->reg_BC);

    ASSERT_EQ(cpu->reg_BC.get(), 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rlc8) {
    cpu->reg_B = 0x8F;
    cpu->rlc8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x1F);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->rlc8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rl8) {
    cpu->reg_B = 0;
    cpu->set_c_flag(1);
    cpu->rl8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x01);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->set_c_flag(0);
    cpu->rl8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rrc8) {
    cpu->reg_B = 0x01;
    cpu->rrc8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x80);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->rrc8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rr8) {
    cpu->reg_B = 0x01;
    cpu->set_c_flag(1);
    cpu->rr8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x80);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->set_c_flag(0);
    cpu->rr8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_sla8) {
    cpu->reg_B = 0x01;
    cpu->sla8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x02);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x80;
    cpu->sla8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_sra8) {
    cpu->reg_B = 0x80;
    cpu->sra8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0xC0);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x01;
    cpu->sra8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_srl8) {
    cpu->reg_B = 0x80;
    cpu->srl8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0x40);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x01;
    cpu->srl8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_bit) {
    bool prev_c_flag;

    cpu->reg_B = 0x01;
    prev_c_flag = cpu->get_c_flag();
    cpu->bit(&cpu->reg_B, 0);

    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_EQ(cpu->get_c_flag(), prev_c_flag);

    cpu->reg_B = 0x01;
    prev_c_flag = cpu->get_c_flag();
    cpu->bit(&cpu->reg_B, 1);

    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_EQ(cpu->get_c_flag(), prev_c_flag);

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    prev_c_flag = cpu->get_c_flag();
    cpu->bit(&cpu->reg_BC, 0);

    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_EQ(cpu->get_c_flag(), prev_c_flag);

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    prev_c_flag = cpu->get_c_flag();
    cpu->bit(&cpu->reg_BC, 1);

    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_EQ(cpu->get_c_flag(), prev_c_flag);
};

TEST(CpuTest, test_set) {
    cpu->reg_B = 0x01;
    cpu->set(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0x01);

    cpu->reg_B = 0x01;
    cpu->set(&cpu->reg_B, 1);

    ASSERT_EQ(cpu->reg_B, 0x03);

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->set(&cpu->reg_BC, 0);

    ASSERT_EQ(mmu->address[0x8000], 0x01);

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->set(&cpu->reg_BC, 1);

    ASSERT_EQ(mmu->address[0x8000], 0x03);
};

TEST(CpuTest, test_res) {
    cpu->reg_B = 0x01;
    cpu->res(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0);

    cpu->reg_B = 0x01;
    cpu->res(&cpu->reg_B, 1);

    ASSERT_EQ(cpu->reg_B, 0x01);

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->res(&cpu->reg_BC, 0);

    ASSERT_EQ(mmu->address[0x8000], 0);

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->res(&cpu->reg_BC, 1);

    ASSERT_EQ(mmu->address[0x8000], 0x01);
};

TEST(CpuTest, test_add8) {
    cpu->reg_B = 0x77;
    cpu->add8(&cpu->reg_B, 0x88);

    ASSERT_EQ(cpu->reg_B, 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x77;
    cpu->add8(&cpu->reg_B, 0x98);

    ASSERT_EQ(cpu->reg_B, 0x0F);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0x77;
    cpu->add8(&cpu->reg_B, 0x89);

    ASSERT_EQ(cpu->reg_B, 0x00);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->add8(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_sub8) {
    cpu->reg_B = 0x77;
    cpu->sub8(&cpu->reg_B, 0x78);

    ASSERT_EQ(cpu->reg_B, 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0x77;
    cpu->sub8(&cpu->reg_B, 0x87);

    ASSERT_EQ(cpu->reg_B, 0xF0);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->sub8(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_and8) {
    cpu->reg_B = 0xFF;
    cpu->and8(&cpu->reg_B, 0xFF);

    ASSERT_EQ(cpu->reg_B, 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0xFF;
    cpu->and8(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_or8) {
    cpu->reg_B = 0xFF;
    cpu->or8(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->or8(&cpu->reg_B, 0);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_xor8) {
    cpu->reg_B = 0xFF;
    cpu->xor8(&cpu->reg_B, 0xFF);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->xor8(&cpu->reg_B, 0xFF);

    ASSERT_EQ(cpu->reg_B, 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_cp8) {
    cpu->reg_B = 0x77;
    cpu->cp8(&cpu->reg_B, 0x78);

    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0x77;
    cpu->cp8(&cpu->reg_B, 0x87);

    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->cp8(&cpu->reg_B, 0);

    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_inc8) {
    cpu->reg_B = 0;
    cpu->inc8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 1);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());

    cpu->reg_B = 0xFF;
    cpu->inc8(&cpu->reg_B);
    
    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
};

TEST(CpuTest, test_dec8) {
    cpu->reg_B = 0;
    cpu->dec8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());

    cpu->reg_B = 1;
    cpu->dec8(&cpu->reg_B);

    ASSERT_EQ(cpu->reg_B, 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
};

TEST(CpuTest, test_add16) {
    bool prev_z_flag;

    cpu->reg_BC.set(0x7700);
    prev_z_flag = cpu->get_z_flag();
    cpu->add16(&cpu->reg_BC, 0x8800);

    ASSERT_EQ(cpu->reg_BC.get(), 0xFF00);
    ASSERT_EQ(cpu->get_z_flag(), prev_z_flag);
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0x7700);
    prev_z_flag = cpu->get_z_flag();
    cpu->add16(&cpu->reg_BC, 0x9800);

    ASSERT_EQ(cpu->reg_BC.get(), 0x0F00);
    ASSERT_EQ(cpu->get_z_flag(), prev_z_flag);
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_BC.set(0x7700);
    prev_z_flag = cpu->get_z_flag();
    cpu->add16(&cpu->reg_BC, 0x8900);

    ASSERT_EQ(cpu->reg_BC.get(), 0x0000);
    ASSERT_EQ(cpu->get_z_flag(), prev_z_flag);
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_BC.set(0);
    prev_z_flag = cpu->get_z_flag();
    cpu->add16(&cpu->reg_BC, 0);

    ASSERT_EQ(cpu->reg_BC.get(), 0);
    ASSERT_EQ(cpu->get_z_flag(), prev_z_flag);
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rl16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0;
    cpu->set_c_flag(1);
    cpu->rl16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0x01);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0;
    cpu->set_c_flag(0);
    cpu->rl16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rlc16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x8F;
    cpu->rlc16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0x1F);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0;
    cpu->rlc16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rrc16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->rrc16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0x80);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0;
    cpu->rrc16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rr16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->set_c_flag(1);
    cpu->rr16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0x80);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0;
    cpu->set_c_flag(0);
    cpu->rr16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_sla16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->sla16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0x02);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x80;
    cpu->sla16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_sra16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x80;
    cpu->sra16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0xC0);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->sra16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_srl16) {
    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x80;
    cpu->srl16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0x40);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0x8000);
    mmu->address[0x8000] = 0x01;
    cpu->srl16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0x8000], 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_ret) {
    cpu->sp = 0xFFFE;
    mmu->address[0xFFFE] = 0x10;
    mmu->address[0xFFFF] = 0x20;
    cpu->ret();

    ASSERT_EQ(cpu->pc, 0x2010 - 1);
    ASSERT_EQ(cpu->sp, 0);
};

TEST(CpuTest, test_store_pc_stack) {
    cpu->pc = 0x2010;
    cpu->sp = 0;
    cpu->store_pc_stack();

    ASSERT_EQ(mmu->address[0xFFFF], 0x20);
    ASSERT_EQ(mmu->address[0xFFFE], 0x11);
    ASSERT_EQ(cpu->sp, 0xFFFE);
};

TEST(CpuTest, test_push16) {
    cpu->reg_BC.set(0x2010);
    cpu->sp = 0;
    cpu->push16(&cpu->reg_BC);

    ASSERT_EQ(mmu->address[0xFFFF], 0x20);
    ASSERT_EQ(mmu->address[0xFFFE], 0x10);
    ASSERT_EQ(cpu->sp, 0xFFFE);
};

TEST(CpuTest, test_pop16) {
    cpu->sp = 0xFFFE;
    mmu->address[0xFFFE] = 0x10;
    mmu->address[0xFFFF] = 0x20;
    cpu->pop16(&cpu->reg_BC);

    ASSERT_EQ(cpu->reg_BC.get(), 0x2010);
    ASSERT_EQ(cpu->sp, 0);
};
