// LCD module connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;


unsigned int temp1,temp2,diff;
int ovcnt=0;

extern void interrupt_init();
extern void capture(unsigned int *temp1,unsigned int *temp2);
extern void intToBCD(int no, char BCDarray[],short size);
extern void convertASCII(char array[],short size);
extern void lcd_disp_int(int no,short row,short col,short size);
extern void ccp1_settings();
extern void timer1_settings();