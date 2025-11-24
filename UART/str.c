#include<lpc21xx.h>
void uart0_config(void);
void uart0_str(unsigned char*);
void uart0_txd(unsigned char);
int main()
{
  uart0_config();
  uart0_str("Embedded");
}
void uart0_config(void)
{
  PINSEL0=0x5;
  U0LCR=0x83;
  U0DLL=97;
  U0DLM=0;
  U0LCR=0x03;
}
void uart0_str(unsigned char*s)
{
  while(*s)
  {
    uart0_txd(*s++);
  }
}
void uart0_txd(unsigned char txd)
{
   while(((U0LSR>>5)&1)==0);
   U0THR=txd;
}
