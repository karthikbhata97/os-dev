#include "idt.h"
#include "types.h"

void set_idt_gate(int intr_num,  u32 handler) {
    idt[intr_num].offset_low = lower_16(handler);
    idt[intr_num].selector = KERNEL_CS;
    idt[intr_num].always0 = 0;
    idt[intr_num].type_attr = 0x8E;
    idt[intr_num].offset_high = upper_16(handler);
}

void load_idtr() {
    idt_reg.base = (u32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__ ("lidtl (%0)" : : "r" (&idt_reg));
}