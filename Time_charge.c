/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// This program starts RF transmission at a selected frequency and output power.
// The program runs for a limited time of hours.
//
// Benny Zelman
// 07.07.13


#include "huma_cc2530_func.c"

#define OUTPUT_POWER    TRANS_POWER(21)         //TX power in dBm

char T1_ovf_cnt = 0;

void main(void)
{
  set32MHzXOSC();
  rfTXConfig(FREQ2405, OUTPUT_POWER);
  timerSetup(TICKS_FREQ025, T1_PRE128);         //set TIMER1 to slowest available clock rate.
  
  /* interrupt setup */
  IEN0 &= ~BIT7;                                //disable global interrupts.
  T1STAT &= ~BIT5;                              //clear TIMER1 overflow IF.
  TIMIF &= BIT6;                                //set TIMER1 overflow IM.
  IEN1 &= BIT1;                                 //set TIMER1 IE.
  IEN0 |= BIT7;                                 //enable global interrupts.
  
  
  T1CTL |= BIT0;                                //start timer1 in free operation mode
  RFST = ISTXON;                                //start RF transmission
  
  while(T1_ovf_cnt < 2);                        //wait for TIMER1 overflow
  RFST = ISRFOFF;
}