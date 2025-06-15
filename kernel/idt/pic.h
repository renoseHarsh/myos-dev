#ifndef PIC_H
#define PIC_H

#include <stdint.h>

void PIC_Initialize(uint8_t offset1, uint8_t offset2);
void PIC_disable(void);
void PIC_sendEOI(uint8_t irq);
uint16_t PIC_get_irr(void);
uint16_t PIC_get_isr(void);

#endif // !PIC_H
