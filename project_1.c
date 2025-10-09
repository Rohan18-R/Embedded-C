#include<lpc21xx.h>
void LCD_INIT(void);
void LCD_CMD(unsigned);
void LCD_DATA(unsigned);
void delay(int);
#define rs 1<<8
#define e 1<<9
#define LCD_D 0xff<<0

int main()
{
	LCD_INIT();
	while(1)
	{
	LCD_DATA('A');
	}
}
void LCD_INIT(void)
{
	IODIR0=LCD_D|rs|e;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
	LCD_CMD(0X80);
}
void LCD_CMD(unsigned cmd)
{
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=rs;
	IOSET0=e;
	delay(2);
	IOCLR0=e;
}
void LCD_DATA(unsigned d)
{
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=rs;
	IOSET0=e;
	delay(2);
	IOCLR0=e;
}
void delay(int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;

}




	