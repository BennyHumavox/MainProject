/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program realizes a simple pulse generator using TIMER1 PWM.
//
// Benny Zelman
// 04.03.13


#include "huma_cc2530_func.c"


void main(void)
{
 
  set32MHzXOSC();
  IEN0 &= ~BIT7;                        //disable global interrupts
  timerSetup(TICKS_FREQ32, T1_PRE1);    //run TIMER1 at 32MHz with no prescaler
    
  /* half the duty cycle */
  T1CC1L = 0x0F;                //buffer the low-order byte     
  T1CC1H = 0x00;                //write the high-order byte and the buffered low-order byte
  
  /* period */
  T1CC0L = 0xFF;
  T1CC0H = 0xFF;
  
  T1CCTL1 |= BIT5;                      //clear output on compare up, set on compare down
  T1CCTL1 |= BIT2;                      //set TIMER1 channel1 compare mode
  P2DIR |= BIT7;                        //set priorities
  
  P0SEL |= BIT3;
  P0DIR |= BIT3;                        //set P0_3 direction to output
//  P0 &= ~BIT3;
  
  //PERCFG &= ~BIT6;                      //use TIMER1 IO alt.1 location
  
  T1CTL |= (BIT1 | BIT0);               //up-down mode
  while(1);
  
}