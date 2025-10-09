#include<lpc21xx.h>
#define LED1 1<<0
#define LED2 1<<1
#define LED3 1<<2
#define Sw 14
unsigned char count=0;
void delay(int ms)
	{
		T0PR=15000-1;
		T0TCR=0x01;
		while(T0TC<ms);
		T0TCR=0x03;
		T0TCR=0x00;
	}
	
int main()
{
	IODIR0=LED1|LED2|LED3;
	IOSET0=LED1|LED2|LED3;
	while(1)
	{
		if(((IOPIN0>>Sw)&1)==0)
		{
			delay(250);
			if(count==0)
			{
				IOCLR0=LED1;
				count++;
			}
			else if(count==1)
			{
				IOSET0=LED1;
				IOCLR0=LED2;
				count++;
			}
			else if(count==2)
			{
				IOSET0=LED2;
				IOCLR0=LED3;
				count=0;
				delay(250);
				IOSET0=LED3;
			}
		}
	}
}

	
	