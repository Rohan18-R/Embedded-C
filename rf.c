#include<lpc21xx.h>
#include<string.h>
void uart_tx(unsigned char);
void uart_config(void);
unsigned char uart_rx(void);
void uart_string(char*);
void delay(int ms);
char ch[20];
int i=0;
#define LED 1<<17
int main()
{
  IODIR0|=LED;
  IOSET0=LED;
  uart_config();
  while(1)
  {
     while(i<12)
	 {
	   ch[i++]=uart_rx();
	 }
	 ch[i]='\0';
	 i=0;
	 uart_string(ch);
	 if((strcmp(ch,"B0600680E1D7"))==0)
	 {
	 IOCLR0=LED;
	 //delay(500);
	 }
	 else
	 {
	  IOSET0=LED;
	  //delay(500);
	 }
  }
}
void uart_config(void)
{
  PINSEL0|=0x5;
  U0LCR=0x83;
  U0DLL=97;
  U0DLM=0;
  U0LCR=0x03;
}
void uart_tx(unsigned char txbyte)
{
  while(((U0LSR>>5)&1)==0);
  U0THR=txbyte;
}
unsigned char uart_rx(void)
{
  while((U0LSR & 0x01)==0);
  return U0RBR;
}
void uart_string( char*str)
{
  while(*str)
  {
    uart_tx(*str++);
  }
}
void delay(int ms)
{
  T0PR=15000-1;
  T0TCR=0x01;
  while(T0TC<ms);
  T0TCR=0x03;
  T0TCR=0x00;
}

 