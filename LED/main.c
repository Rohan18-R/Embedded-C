#include<lpc21xx.h>
#include"types.h"
#include"i2c_h.h"
#include"i2c_eeprom.h"
#include"delay.h"
#include"LCD_INIT.h"
//#define gLED 1<<16 //p1.16
//#define rLED 1<<17 //p1.17
int main()
{
   u8 ch;
   LCD_INIT();
   init_i2c();
   i2c_eeprom_write(0x50,0x00,'A');
   while(1)
   {
    ch=i2c_eeprom_read(0x50,0x00);
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	LCD_string("Vehicle count");
	LCD_CMD(0xc1);
    LCD_DATA(ch);
    delay(1000);
   }
 
}
