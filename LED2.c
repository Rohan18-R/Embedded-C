#include<lpc21xx.h>
#include"delay.h"
#define LED1 1<<0
#define LED2 1<<1
int main()
{
IODIR0=LED1|LED2;
while(1)
{
IOCLR0=LED1|LED2;
delay(500);
IOSET0=LED1|LED2;
delay(500);
}
}
