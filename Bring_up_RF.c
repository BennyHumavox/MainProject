/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// Test program for PCB bring up procedure.
// This program created a PWM signal using RF transmission using TIMER3.
// 
//
// Benny Zelman
// 09.07.13


#include "huma_cc2530_func.c"

#define OUTPUT_POWER                    TRANS_POWER(10)                                                //transmission power in dBm

void main(void)
{
   /* device setup */
  set32MHzXOSC();
//  timerSetup(TICKS_FREQ025, T1_PRE8);         //set TIMER1 to slowest available clock rate.
  rfTXConfig(FREQ2405, OUTPUT_POWER);
  CSPT = 0xFF;
  
  /* RF5602 power down pin */
  P0DIR |= BIT7;    //set P0 BIT7 as output
  P0 |= BIT7;       //set BIT7 to high
  
  RFST = ISTXON;
  
  while(1);
}