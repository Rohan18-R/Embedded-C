#include<lpc21xx.h>
#define LED 1<<0
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
 IODIR0=LED;
 while(1)
 {
  IOCLR0=LED;
  delay(500);
  IOSET0=LED;
  delay(500);
 }
 }

