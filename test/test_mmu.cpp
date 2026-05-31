#include "tests.h"


class MmuTest : public ::testing::Test {
protected:
    Cartridge* c;
    Mmu* mmu;

    void SetUp() override {
        c = new Cartridge("/mnt/c/Users/Utilizador/Desktop/projects/GB_EMU/roms/cpu_instrs/cpu_instrs.gb");
        mmu = new Mmu(c);
    }

    void TearDown() override {
        delete mmu;
        delete c;
    }
};

TEST_F(MmuTest, basic_wram_read_write) {
    mmu->write_memory(0xC000, 0x42);
    EXPECT_EQ(mmu->read_memory(0xC000), 0x42);
}

TEST_F(MmuTest, rom_is_readonly) {
    uint8_t original = mmu->read_memory(0x0100);

    mmu->write_memory(0x0100, 0xFF);

    EXPECT_EQ(mmu->read_memory(0x0100), original);
}

TEST_F(MmuTest, echo_ram_mirrors_wram) {
    mmu->write_memory(0xC123, 0x77);

    EXPECT_EQ(mmu->read_memory(0xE123), 0x77);
}


TEST_F(MmuTest, wram_mirror_consistency) {
    mmu->write_memory(0xD456, 0x33);

    EXPECT_EQ(mmu->read_memory(0xF456), 0x33);
}

TEST_F(MmuTest, oam_read_write) {
    mmu->write_memory(0xFE10, 0x99);
    EXPECT_EQ(mmu->read_memory(0xFE10), 0x99);
}

TEST_F(MmuTest, oam_protection_placeholder) {
    mmu->write_memory(0xFE00, 0x12);
    EXPECT_EQ(mmu->read_memory(0xFE00), 0x12);
}

TEST_F(MmuTest, address_wrapping_does_not_crash) {
    mmu->write_memory(0xFFFF, 0xAA);
    EXPECT_EQ(mmu->read_memory(0xFFFF), 0xAA);
}

TEST_F(MmuTest, hram_read_write) {
    mmu->write_memory(0xFF80, 0x55);
    EXPECT_EQ(mmu->read_memory(0xFF80), 0x55);
}

TEST_F(MmuTest, no_null_pointer_crashes) {
    for (uint16_t addr = 0x0000; addr < 0x200; addr++) {
        mmu->write_memory(addr, 0x12);
        EXPECT_NO_THROW(mmu->read_memory(addr));
    }
}

TEST_F(MmuTest, full_memory_smoke) {
    // Test WRAM (0xC000 - 0xDFFF)
    for (uint16_t addr = 0xC000; addr <= 0xDFFF; addr += 0x111) {
        mmu->write_memory(addr, addr & 0xFF);
        ASSERT_EQ(mmu->read_memory(addr), addr & 0xFF);
    }

    // Test HRAM (0xFF80 - 0xFFFE)
    for (uint16_t addr = 0xFF80; addr <= 0xFFFE; addr += 0x11) {
        mmu->write_memory(addr, addr & 0xFF);
        ASSERT_EQ(mmu->read_memory(addr), addr & 0xFF);
    }
}