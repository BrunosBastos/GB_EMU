#include "tests.h"

class HaltTest : public ::testing::Test {
public:
    ~HaltTest() override {}
    Emulator* emulator;
    std::string filename;

    void SetUp() override {
        filename = "/mnt/c/Users/Utilizador/Desktop/projects/GB_EMU/test/test_roms/cpu_instrs/cpu_instrs.gb";
        emulator = new Emulator(&filename);
    }

    void TearDown() override {
        free(emulator);
    }
};


TEST_F(HaltTest, test_halt_bug) {
    emulator->reset(&filename);

    emulator->run();
    


    ASSERT_TRUE(false);
};

