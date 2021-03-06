#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/idt.h>
#include <kernel/tty.h>

extern setidt(void);
void add_idt_entry(int n,uint32_t base,uint16_t cs_selector,uint8_t flags){
	idt[n].base_low = (uint16_t) base;
	idt[n].cs_selector = cs_selector;
	idt[n].zero = 0;
	idt[n].flags = flags;
	idt[n].base_high = (uint16_t) (base >> 16);
}
void init_idt(void){
	log_info("init idt","idt");
	idtp.limit = sizeof(struct idt_entry) * 256 - 1; 
	idtp.base = &idt;
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
	setidt();
	ok();
}
