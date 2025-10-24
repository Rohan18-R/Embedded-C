#include<lpc21xx.h>
void uart0_config(void);
void uart0_txt(unsigned char);
unsigned char uart0_rxt(void);
int main()
{
  unsigned char rxbyte;
  uart0_config();
  while(1)
  {
    rxbyte=uart0_rxt();
	uart0_txt(rxbyte);
  }
}
void uart0_config(void)
{
  PINSEL0=0x5;
  U0LCR=0x83;
  U0DLL=97;
  U0DLM=0;
  U0LCR=0x03;
}
void uart0_txt(unsigned char rxt)
{
  while(((U0LSR>>5)&1)==0);
  U0THR=rxt;
}
unsigned char uart0_rxt(void)
{
  while((U0LSR & 0x1)==0);
  return U0RBR;
}

