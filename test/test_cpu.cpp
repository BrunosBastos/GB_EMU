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

    ASSERT_TRUE(cpu->reg_B == 0x21);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->swap8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_swap16) {
    cpu->reg_BC.set(0x1234);
    cpu->swap16(&cpu->reg_BC);

    ASSERT_TRUE(cpu->reg_BC.get() == 0x3412);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_BC.set(0);
    cpu->swap16(&cpu->reg_BC);

    ASSERT_TRUE(cpu->reg_BC.get() == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rlc8) {
    cpu->reg_B = 0x8F;
    cpu->rlc8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0x1F);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->rlc8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rl8) {
    cpu->reg_B = 0;
    cpu->set_c_flag(1);
    cpu->rl8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0x01);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->set_c_flag(0);
    cpu->rl8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rrc8) {
    cpu->reg_B = 0x01;
    cpu->rrc8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0x80);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->rrc8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_rr8) {
    cpu->reg_B = 0x01;
    cpu->set_c_flag(1);
    cpu->rr8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0x80);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());

    cpu->reg_B = 0;
    cpu->set_c_flag(0);
    cpu->rr8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());
};

TEST(CpuTest, test_sla8) {
    cpu->reg_B = 0x01;
    cpu->sla8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0x02);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x80;
    cpu->sla8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_sra8) {
    cpu->reg_B = 0x80;
    cpu->sra8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0xC0);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x01;
    cpu->sra8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_srl8) {
    cpu->reg_B = 0x80;
    cpu->srl8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0x40);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(!cpu->get_c_flag());

    cpu->reg_B = 0x01;
    cpu->srl8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
    ASSERT_TRUE(cpu->get_c_flag());
};

TEST(CpuTest, test_bit) {
    ASSERT_TRUE(true);
};

TEST(CpuTest, test_set) {
    ASSERT_TRUE(true);
};

TEST(CpuTest, test_res) {
    ASSERT_TRUE(true);
};

TEST(CpuTest, test_srl16) {
    ASSERT_TRUE(true);
};

TEST(CpuTest, test_inc8) {
    cpu->reg_B = 0;
    cpu->inc8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 1);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());

    cpu->reg_B = 0xFF;
    cpu->inc8(&cpu->reg_B);
    
    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(!cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());
};

TEST(CpuTest, test_dec8) {
    cpu->reg_B = 0;
    cpu->dec8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0xFF);
    ASSERT_TRUE(!cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(cpu->get_h_flag());

    cpu->reg_B = 1;
    cpu->dec8(&cpu->reg_B);

    ASSERT_TRUE(cpu->reg_B == 0);
    ASSERT_TRUE(cpu->get_z_flag());
    ASSERT_TRUE(cpu->get_n_flag());
    ASSERT_TRUE(!cpu->get_h_flag());
};
