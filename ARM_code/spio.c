#include "spio.h"
#include "string.h"

char SPIO_buff[512];
int SPIO_done = 0;
int SPIO_index = 0;

void SPIO_enable(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16);

	LPC_IOCON->PIO0_2 &= ~0x07;
	LPC_IOCON->PIO0_2 |= 0x01;

	LPC_IOCON->PIO0_8 &= ~0x07;
	LPC_IOCON->PIO0_8 |= 0x01;

	LPC_IOCON->PIO0_9 &= ~0x07;
	LPC_IOCON->PIO0_9 |= 0x01;

	LPC_IOCON->PIO0_6 &= ~0x07;
	LPC_IOCON->PIO0_6 |= 0x02;

	LPC_IOCON->SCK_LOC |= 0x02;

	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 11);

	LPC_SYSCON->SSP0CLKDIV = 0x04;

	LPC_SYSCON->PRESETCTRL  |= 0x01;

	LPC_SSP0->CR0 = 0xFFC7;
	LPC_SSP0->CR1 |= 0x02;
	LPC_SSP0->CPSR = 0x02;

	while(LPC_SSP0->SR & 0x04 == 1){
		int tmp = LPC_SSP0->DR;
	}
}

int SPIO_send(char* buf, int size){
	int i = 0;

	while(LPC_SSP0->SR & 0x01 != 0 && i < size){
		LPC_SSP0->DR = *(buf+i);
		i += 1;
	}
	return 0;
}

int SPIO_recv(char* buf){

	while(!SPIO_done);
	memcpy(buf, SPIO_buff, SPIO_index);
	SPIO_done = 0;
	SPIO_index = 0;
	LPC_SSP0->ICR |= 0x02;

 	return SPIO_index;
}

