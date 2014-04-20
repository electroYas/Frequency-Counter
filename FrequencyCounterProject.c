#include "FrequencyCounter.h"

void interrupt(){
 if(TMR1IF_BIT==1){
    TMR1IF_BIT=0;
    ovcnt++;
  }
}

void main() {
long frequency,period;
int frac;

  ADCON1= 0X0F;                  //ALL ADC pin as digital
  CMCON = 0X07;                  //Comparators off
  TRISC.F2 = 1;                  //capture pin input
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  ccp1_settings();                  //capture settings for rising edges
  timer1_settings();

  Lcd_Out(1,1,"Frequency meter");
  interrupt_init();                     //interrupt for overflow of the timer1
  while(1){
    capture(&temp1,&temp2);             //capture at rising edges

    if(temp1>temp2) ovcnt--;            //correcting overflow count
    diff = temp2-temp1;                 //getting time difference
    period = ovcnt* 65536 + diff;       //get the total time

    frequency = (unsigned long)10000000/period;    //calculate the frequency
    if(frequency >=1000){
      frac = frequency %1000;
      frequency = frequency /1000;
      Lcd_Out(2,10,"kHz");
    }else{
      frac = 0;
      Lcd_Out(2,10," Hz");
    }
    lcd_disp_int((unsigned int)frequency,2,1,5) ;
    Lcd_Chr(2,6,'.');
    lcd_disp_int(frac,2,7,3) ;
    delay_ms(100);
  }
}