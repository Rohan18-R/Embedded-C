#include<lpc21xx.h>
#include"LCD_INIT.h"
void uart_config(void);
unsigned char uart_rx(void);
void uart_tx(unsigned char);
int main()
{
  unsigned char rxbyte;
  LCD_INIT();
  uart_config();
  while(1)
  {
    rxbyte=uart_rx();
	//LCD_CMD(0x80);
	LCD_DATA(rxbyte^32);
	uart_tx(rxbyte);

  }
}
void uart_config(void)
{
  PINSEL0=5<<16;
  U1LCR=0x83;
  U1DLL=97;
  U1DLM=0;
  U1LCR=0x03;
}
unsigned char uart_rx(void)
{
   while((U1LSR & 0x1)==0);
   return U1RBR;
}
void uart_tx(unsigned char txbyte)
{
   while(((U1LSR>>5)&1)==0);
   U1THR=txbyte;
}
