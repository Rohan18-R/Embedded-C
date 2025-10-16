#include<lpc21xx.h>
#include"LCD_INIT.h"
#include"delay.h"
void cgram_write(void);
unsigned char cgram_lut[]={0x0e,0x11,0x11,0x11,0x11,0x11,0x11,0x0e};
unsigned char a=0x80,b=0xc0,count=0;
int main()
{
  LCD_INIT();
  while(1)
  {
  cgram_write();
  for(i=0,j=0;(i<32&&j<32);i+=1,j+=1)
  {
   if(count%2==0)
   {                                                                                                                                                                                                                                                                                          
    LCD_CMD(b+i);
	  LCD_DATA(0);
    delay(500);
    LCD_CMD(0x01);
   }
   else
   {
    LCD_CMD(a+i);
	  LCD_DATA(0);
    delay(500);
    LCD_CMD(0x01);
   }
    count++;
  } 
}
void cgram_write(void)
{
   char i=0;
   LCD_CMD(0x40);
   for(i=0;i<8;i++)
   {
   LCD_DATA(cgram_lut[i]);
   }
   delay(500);
}
