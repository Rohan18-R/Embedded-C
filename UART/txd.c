#include<lpc21xx.h>
void uart_config(void);
void uart_txd(unsigned char);
int main()
{
  uart_config();
  while(1)
  {
    uart_txd('A');
  }
}
void uart_config(void)
{
   PINSEL0=0x5;
   U0LCR=0x83;
   U0DLL=97;
   U0DLM=0;
   U0LCR=0x03;
}
void uart_txd(unsigned char txd)
{
  while(((U0LSR>>5)&1)==0);
  U0THR=txd;
}
