#include<lpc21xx.h>
#include"delay.h"
#define LED1 1<<0
#define LED2 1<<1
int main()
{
 IODIR0=LED1|LED2;
 IOSET0=LED1|LED2;
 while(1)
 {
   unsigned int i;
   for(i=0;i<15;i++)
   {
     if(i<10)
	 {
	  IOCLR0=LED1;
	  delay(1000);
	  IOSET0=LED1;
	  delay(1000);
	 }
	 else
	 {
	 IOCLR0=LED2;
	 delay(500);
	 IOSET0=LED2;
	 delay(500);
	 }
   }
  }
 }