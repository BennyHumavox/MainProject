/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program programs the CSP to start and stop transmission for defined periods of time using MAC TIMER.
// It will be used to test communication protocol by transmitting a 2-bit sync word followed by an 8-bit word.
// sync word = '01', default word = '0xFF'
// Benny Zelman
// 17.01.13
//INCOMPLETE

#include "huma_cc2530_func.c"

#pragma vector = 0x83
//void RF_ISR(void) __interrupt 16
__interrupt void rfIsr(void) 
{
  IEN0 &= ~BIT7;                //disable global interrupts
  
  if(RFIRQF1 & BIT5)             //CSP_WAIT IF
  {
    RFIRQF1 &= ~BIT5;             //clear CSP_WAIT IF
    S1CON = 0x00;                 //clear general RF IF
  }
  if(RFIRQF1 & BIT4)           //CSP_STOP IF
  {
  }
  
  IEN0 |= BIT7;                //enable global interrupts
}

#define OUTPUT_POWER                    TRANS_POWER(21)                                                 //transmission power in dBm
#define T1_PRE                          T1_PRE1                                                       //select TIMER1 prescaler 1, 8, 32, 128
#define TIMER_TICKS                     TICKS_FREQ32
#define WORD_LEN                        8

  unsigned char RFST_read;
void main(void)
{
  unsigned char tmp = 0;

  
  IEN0 &= ~BIT7;                //disable global interrupts
  set32MHzXOSC();
  rfTXConfig(FREQ2405, POWER_0DBM);
  
  CSPY = 0x1F;
  /* settings for TIMER2 period and duty cycle */
  //TIMER2 period
  T2MSEL = 0x02;        //mux select t2_per
  T2M0 = 0x00;
  T2M1 = 0x02;
  //TIMER2 duty cycle
  T2MSEL = 0x03;        //mux select t2_cmp1
  T2M0 = 0x00;
  T2M1 = 0x01;
  
  T2EVTCFG |= (0x07 & 0x01);     //set TIMER2 event1 to compare1
  T2EVTCFG |= (0x70 & 0x00);     //set TIMER2 event2 to period
  
  rf_prog();
 
  T2CTRL &= ~BIT1;               //start of TIMER2 is synced with 32MHz clock
  T2CTRL |= BIT0;               // start TIMER2 operation
  while(T2CTRL & BIT2);
  RFST_read = RFST;

  while(1)
  {
    //timer2Setup();
    if(!tmp)
    {
      RFST = ISSTART;           // start CSP program execution
      
      tmp++;
    }
    if(!CSPY) CSPY = 0x0A;
//    RFST_read = RFST;
 
  }
}

