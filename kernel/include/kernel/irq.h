#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H

#include <stddef.h>


void init_irq(void);
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
#endif
