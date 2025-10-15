#include<lpc21xx.h>
void ext_int0_isr(void)__irq;
void ext_int1_isr(void) __irq;
void  FIQ_Handler(void) __irq;
void delay(int);
int main()
{
  unsigned char count=0;
  IODIR0=0x07;
  IOSET0=0x07;
  PINSEL1=0x1;
  PINSEL0=1<<29|3<<14;
  VICIntSelect=1<<14|0<<15|0<<16;
  VICVectCntl0=0x20|15;
  VICVectAddr0=(unsigned long)ext_int0_isr;
  VICDefVectAddr=(unsigned long)ext_int1_isr;
  EXTMODE=0x07;
  EXTPOLAR=0x00;
  VICIntEnable=(1<<14)|(1<<15)|(1<<16);
  while(1)
  {
    count++;
  }
}
void ext_int0_isr(void)__irq
{
  EXTINT=0x01;
  IOCLR0=1<<0;
  delay(500);
  IOSET0=1<<0;
  VICVectAddr=0;
}
void ext_int1_isr(void) __irq
{
  EXTINT=0x02;
  IOCLR0=1<<1;
  delay(500);
  IOSET0=1<<1;
  delay(500);
  VICVectAddr=0;
}
void  FIQ_Handler(void) __irq
{
  EXTINT=0x04;
  IOCLR0=1<<2;
  delay(500);
  IOSET0=1<<2;
  delay(500);
}
void delay(int ms)
{
 T0PR=15000-1;
 T0TCR=0x01;
 while(T0TC<ms);
 T0TCR=0x03;
 T0TCR=0x00;
 }
