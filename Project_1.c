#include<lpc21xx.h>
void exint0_isr(void) __irq
{
	EXTINT=0x01;
	IOSET0=1<<0;
	IOCLR0=1<<0;
	VICVectAddr=0;
}
int main()
{
	unsigned int count=0;
	PINSEL1=0x1;
	IODIR0=1<<0;
	VICIntSelect=0;
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(unsigned long)exint0_isr;
	EXTMODE=0x00;
	EXTPOLAR=0x01;
	VICIntEnable=1<<14;
	while(1)
	{
		count++;
	}
	
}


	