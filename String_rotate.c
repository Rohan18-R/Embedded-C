#include<lpc21xx.h>
#include"LCD_INIT.h"
#include"delay.h"
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_string(unsigned char*);
unsigned char a=0x80;
int main()
{
   LCD_INIT();
   while(1)
   { 
   LCD_string("Embedded");
   LCD_CMD(a++);
   if(a==0x90)
   a=0x80;
   LCD_CMD(0x01);
   } 
}
void LCD_string(unsigned char *s)
{
   char b=a;
   while(*s)
   { 
     LCD_CMD(b++);
	 LCD_DATA(*s++);
	 if(b==0x90)
	 b=0x80;
	 
   }
   delay(500);
}


