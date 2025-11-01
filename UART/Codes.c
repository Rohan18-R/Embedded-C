#include<lpc21xx.h>
#include"delay.h"
#include"lcd_header.h"
void uart_config(void);
void uart_interupt(void);
void uart_tx(unsigned char);
void uart_int(void) __irq
{
	unsigned char x=U0RBR;
	char *s="give valid input";
	if(x=='1')
	{
		IOCLR0=0X04;
		IOSET0=0X08;
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string("LCD 1 IS ON");
	}	
	else if(x=='2')
	{
		IOCLR0=0X08;
		IOSET0=0X04;
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string("LCD 2 IS ON");
	}
	else
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		while(*s)
		 lcd_data(*s++);
	}
	VICVectAddr=0;
}
int main()
{
	IODIR0=3<<2;
	IOSET0=3<<2;
	lcd_init();
	uart_config();
	uart_interupt();

	while(1);
}
void uart_config(void)
{
	PINSEL0|=0X5;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}			  
void uart_interupt(void)
{
	VICIntSelect=0;
	VICVectCntl0=0x20|6;
	VICVectAddr0=(unsigned long)uart_int;
	VICIntEnable=1<<6;

	U0IER=0X01;
}
void uart_tx(unsigned char s)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=s;
}

