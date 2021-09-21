#pragma once

#include "types.h"


void set_bit(byte *data, byte bit, bool value) {
    *data = (*data & ~(1 << bit)) | (value << bit);
};

bool get_bit(byte *data, byte bit) {
    return *data & (1 << bit);
};

word combine(byte high, byte low) {
    return (high << 8 | low);
};



/* PairRegister */

PairRegister::PairRegister(byte *high, byte *low) {
    this->hi = high;
    this->lo = low;
};

word PairRegister::get() {
    return *lo | (*hi << 8);
};

byte PairRegister::high() {
    return *hi;
};

byte PairRegister::low() {
    return *lo;
};

void PairRegister::high(byte value) {
    *hi = value;
};

void PairRegister::low(byte value) {
    *lo = value;
};

void PairRegister::set(word value) {
    *hi = (value & 0xFF00) >> 8;
    *lo = value & 0x00FF;
};

void PairRegister::set(byte hi, byte lo) {
    *(this->hi) = hi;
    *(this->lo) = lo;
};

PairRegister PairRegister::operator++() {
    set(get() + 1);
};

PairRegister PairRegister::operator--() {
    set(get() - 1);
};



/* MemoryRegister */

MemoryRegister::MemoryRegister(byte *addr) {
    data = addr;
};

byte MemoryRegister::get() {
    return *data;
};

void MemoryRegister::set(byte value) {
    *data = value;
};

void MemoryRegister::set_bit(byte bit, bool value) {
    *data |= (*data & ~(1 << bit)) | (1 << bit);
};

bool MemoryRegister::get_bit(byte bit) {
    return *data & (1 << bit);
};
