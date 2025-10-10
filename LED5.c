#include<lpc21xx.h>
#include"delay.h"
#define LED 0xff<<0
int main()
{
 unsigned char i;
 IODIR0=LED;
 IOSET0=LED;
 while(1)
 {
   for(i=8;i>0;i--)
   {
     IOCLR0=1<<i;
	 delay(500);
	 IOSET0=1<<i;
	 delay(500);
   }
 }
}

   