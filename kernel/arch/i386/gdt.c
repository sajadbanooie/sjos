#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/gdt.h>
#include <kernel/tty.h>

extern void setgdt(void);
extern void reloadseg(void);
//extern void gdt_flush(void);
extern settss(void);
extern void *stack_top;

void add_gdt_entry(int n,uint32_t base,uint32_t limit,uint8_t flags,uint8_t access){
	gdt[n].limit_low = (limit & 0xFFFF);
	gdt[n].base_low = (uint16_t) (base & 0xFFFF);
	gdt[n].base_middle = (uint8_t) ((base & 0xFF0000) >> 16);
	gdt[n].access = access;
	gdt[n].limit_high_flags = (limit & 0x0F0000) >> 16;
	gdt[n].limit_high_flags |= (flags & 0xF0);
	gdt[n].base_high = (uint8_t) ((base & 0xFF000000) >> 24);
}
void install_tss(void){
	memset ((void*) &TSS, 0, sizeof (struct tss_entry));

	TSS.ss0 = 0x10;
	TSS.esp0 = &stack_top;
	
	// TSS.cs=0x0b;
	// TSS.ss = 0x13;
	// TSS.es = 0x13;
	// TSS.ds = 0x13;
	// TSS.fs = 0x13;
	// TSS.gs = 0x13;

	//! flush tss
	settss ();
}
void init_gdt(void){
	log_info("init gdt\n","gdt");
	gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
    	gp.base = &gdt;
	// null
	log_info("seting null","gdt");
	add_gdt_entry(0, 0, 0, 0, 0);
	ok();
	// kernel cs
	log_info("seting code segment","gdt");
	add_gdt_entry(1, 0, 0xFFFFFFFF, 0xCF, 0x9A);
	ok();
	// kernel ds
	log_info("seting data segment","gdt");
	add_gdt_entry(2,0, 0xFFFFFFFFF, 0xCF, 0x92);
	ok();
	log_info("seting usermode code segment","gdt");
	add_gdt_entry(3, 0, 0xFFFFFFFF, 0xCF, 0xFA);
	ok();
	// kernel ds
	log_info("seting usermode data segment","gdt");
	add_gdt_entry(4,0, 0xFFFFFFFFF, 0xCF, 0xF2);
	ok();
	log_info("seting gdt ptr","gdt");
	add_gdt_entry(5,&TSS,sizeof(TSS), 0, 0xE9);
	ok();
	log_info("seting gdt ptr","gdt");
	setgdt();
	ok();
	log_info("reloading segments","gdt");
	reloadseg();
	//install_tss();
	ok();

}

