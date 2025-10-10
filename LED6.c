 #include<lpc21xx.h>
 #include"delay.h"
 #define LED 0xff<<0
 int main()
 {
   int i;
   IODIR0=LED;
   IOSET0=LED;
   while(1)
   {
   for(i=-7;i<=7;i++)
   {
     if(i<0)
	 {
	  IOCLR0=1<<i+7;
	  delay(500);
	  IOSET0=1<<i+7;
	  delay(500);
	 }
	 else
	 {
	  IOCLR0=1<<7-i;
	  delay(500);
	  IOSET0=1<<7-i;
	  delay(500);
	 }
	}
  }
}