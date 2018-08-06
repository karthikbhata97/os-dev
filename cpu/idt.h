#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CS 0x8

typedef struct {
    u16 offset_low;
    u16 selector;
    u8 always0;
    u8 type_attr;
    u16 offset_high;
}__attribute__((packed)) idt_gate_t;

typedef struct {
    u16 limit;
    u32 base;
}__attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void load_idtr();
void set_idt_gate(int n, u32 handler);

#endif