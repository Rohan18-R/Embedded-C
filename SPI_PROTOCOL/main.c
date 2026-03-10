#include <lpc21xx.h>
#include <stdio.h>

/* ----------- MACROS ----------- */
#define MSTR 5
#define SPIF 7

#define CS (1<<7)

#define LCD_D  ((0xF<<10)|(0xF<<14))
#define RS (1<<8)
#define E  (1<<9)

/* ----------- FUNCTION PROTOTYPES ----------- */
void SPI_INIT(void);
unsigned char SPIO(unsigned char data);

float Read_ADC_MCP3204(unsigned char channel_no);

void delay(int ms);

void LCD_INIT(void);
void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char d);
void LCD_string(unsigned char *s);
void LCD_float(float num);

/* ----------- SPI INITIALIZATION ----------- */
void SPI_INIT(void)
{
    PINSEL0 |= 0x00001500;      // Enable SPI pins P0.4 P0.5 P0.6
    S0SPCCR = 150;              // SPI clock
    S0SPCR = (1<<MSTR) | 0x18;  // Master mode, Mode 3

    IODIR0 |= CS;
    IOSET0 = CS;
}

/* ----------- SPI DATA TRANSFER ----------- */
unsigned char SPIO(unsigned char data)
{
    unsigned char stat;

    stat = S0SPSR;        // Clear SPIF
    S0SPDR = data;        // Load data

    while(((S0SPSR >> SPIF) & 1) == 0); // Wait for completion

    return S0SPDR;        // Return received data
}

/* ----------- READ MCP3204 ADC ----------- */
float Read_ADC_MCP3204(unsigned char channel_no)
{
    unsigned char hbyte, lbyte;
    unsigned int adcval = 0;

    IOCLR0 = CS;

    SPIO(0x06);                   // Start + Single ended
    hbyte = SPIO(channel_no<<6);  // Channel selection
    lbyte = SPIO(0x00);           // Dummy read

    IOSET0 = CS;

    adcval = ((hbyte & 0x0F)<<8) | lbyte;

    return ((adcval * 3.3) / 4095);   // Convert to voltage
}

/* ----------- DELAY USING TIMER ----------- */
void delay(int ms)
{
    T0PR = 15000 - 1;
    T0TCR = 0x01;

    while(T0TC < ms);

    T0TCR = 0x03;
    T0TCR = 0x00;
}

/* ----------- LCD INITIALIZATION ----------- */
void LCD_INIT(void)
{
    IODIR0 |= LCD_D | RS | E;

    LCD_CMD(0x38);   // 8-bit mode
    LCD_CMD(0x0C);   // Display ON
    LCD_CMD(0x01);   // Clear display
    LCD_CMD(0x80);   // Cursor position
}

/* ----------- LCD COMMAND ----------- */
void LCD_CMD(unsigned char cmd)
{
    IOCLR0 = LCD_D;

    IOSET0 = (cmd << 10);   // Send command

    IOCLR0 = RS;

    IOSET0 = E;
    delay(2);
    IOCLR0 = E;
}

/* ----------- LCD DATA ----------- */
void LCD_DATA(unsigned char d)
{
    IOCLR0 = LCD_D;

    IOSET0 = (d << 10);     // Send data

    IOSET0 = RS;

    IOSET0 = E;
    delay(2);
    IOCLR0 = E;
}

/* ----------- LCD STRING ----------- */
void LCD_string(unsigned char *s)
{
    while(*s)
    {
        LCD_DATA(*s++);
    }
}

/* ----------- LCD FLOAT ----------- */
void LCD_float(float num)
{
    char str[20];

    sprintf(str,"%.2f",num);

    LCD_string(str);
}

/* ----------- MAIN FUNCTION ----------- */
int main()
{
    float res;

    SPI_INIT();
    LCD_INIT();

    while(1)
    {
        res = Read_ADC_MCP3204(0);

        LCD_CMD(0x80);
        LCD_string("Voltage:");

        LCD_CMD(0xC0);
        LCD_float(res);

        delay(2000);
    }
}

