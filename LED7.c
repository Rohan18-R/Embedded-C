#include<lpc21xx.h>
#include"delay.h"
#define LED 0xff
int main()
{
 int i,j;
 IODIR0=LED;
 IOSET0=LED;
 while(1)
 {
 for(i=0,j=7;((i<=j)|(j<=i));i++,j--)
 {
   	 IOCLR0=1<<i|1<<j;
	 delay(500);
	 IOSET0=1<<i|1<<j;
	 delay(500);
  
 }
 }
 }
 