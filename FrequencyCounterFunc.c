extern int ovcnt=0;
void interrupt_init(){
  INTCON=0;
  TMR1IF_BIT=0;
  TMR1IE_BIT=0;
  PEIE_BIT =1;
  CCP1IF_BIT = 0;
  CCP1IE_BIT = 0;
  GIE_BIT=1;
}

void capture(unsigned int *temp1,unsigned int *temp2){

  ovcnt =0;
  TMR1ON_BIT = 1;
  CCP1IF_BIT=0;
  TMR1IF_BIT=0;
  TMR1IE_BIT=0;
  while(CCP1IF_BIT==0);
  *temp1 = CCPR1;
  CCP1IF_BIT = 0;
  TMR1IF_BIT=0;
  TMR1IE_BIT=1;
  while(CCP1IF_BIT==0);
  TMR1ON_BIT = 0;
  *temp2 = CCPR1;

}
void intToBCD(int no, char BCDarray[],short size)
{
 short buff;
 short temp=0;
 buff=size;
 for(buff=size;buff>=0;buff--)
 {
  BCDarray[buff]=no%10;
  no=no/10;
 }
}

void convertASCII(char array[],short size)
{
 short buff;
 buff=size;
 for(buff=size;buff>=0;buff--)
 {
  array[buff]|=0x30;
  if(array[buff] > 0x39) array[buff]+=7;
 }
}

void lcd_disp_int(int no,short row,short col,short size)
{
 char BCDarray[5];
 int i;
 int j;
 int val;
 if(no<0){
   val = ~no;
   val = val + 1;
 }else{
   val = no;
 }
 for(i=0;i<5;i++) BCDarray[i] = 0;
 size--;
 intToBCD(val,BCDarray,size);
 convertASCII(BCDarray,size);
 Lcd_Chr(row,col,BCDarray[0]);
 if(size>=1) for(j=1;j<=size;j++) Lcd_Chr_Cp(BCDarray[j]);

}
void ccp1_settings(){
  CCP1CON =0;
  CCP1M3_BIT = 0;
  CCP1M2_BIT = 1;
  CCP1M1_BIT = 0;
  CCP1M0_BIT = 1;
}

void timer1_settings(){
  RD16_BIT = 1;
  T1RUN_BIT = 0;
  T1CKPS1_BIT = 0;
  T1CKPS0_BIT = 0;
  T1OSCEN_BIT = 0;
  T1SYNC_BIT = 0;
  TMR1CS_BIT = 0;
  TMR1ON_BIT = 1;
}