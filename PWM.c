/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program creates a PWM signal on selected pin using TIMER3
// T3CC0, T3CC1 holds PWM period and DC in TIMER3 steps.
// By default the counter works with 32Mhz ticks and no prescaler, with step time of 31.25 nanosecond.
// Timer Step Time = prescaler / (ticks freq.)
//
// Benny Zelman
// 15.01.13


#include "huma_cc2530_func.c"


void main(void)
{
 
  set32MHzXOSC();
  IEN0 &= ~BIT7;                 //disable global interrupts
  
  CLKCONCMD |= (BIT5 | BIT4 | BIT3);   //set ticks freq. 0.25MHz
  PERCFG &= ~BIT5;                      //set TIMER3 alt. 1 location
//  PERCFG |= BIT5;                       //set TIMER3 alt. 2 location
  P2SEL |= (BIT6 | BIT5);               //prioritize TIMER3 over USART1 over USART0
  
  P1SEL |= BIT3;                        //use P1_3 as peripheral function
  P1DIR |= BIT3;                        //P1_3 direction to output
//  P1SEL |= BIT7;                        //use P1_7 as peripheral function
//  P1DIR |= BIT7;                        //P1_7 direction to output
 
//  T3CTL &= ~BIT3;                       //clear TIMER3 IM
  T3CTL |= BIT3;                        //enable TIMER3 overflow IM
  
//  T3CTL = (T3CTL & ~BIT0) | BIT1;       //set TIMER3 modulo mode  
  
  
//  T3CTL &= ~(BIT7 | BIT5 |BIT6);      //set TIMER3 prescaler to 1
  T3CTL |= (BIT7 | BIT6 | BIT5);        //set TIMER3 prescaler to 128
  
  T3CC0 = 0xAF;                         //TIMER3 compare value
  //  T3CC1 = 0x33;                         //TIMER3 DC
  
  //  T3CCTL0 &= ~BIT6;                     //clear channel0 IM
  T3CCTL0 |= BIT2;                      //channel0 compare mode       
  T3CCTL0 |= (BIT5 | BIT4);             //(channel0) clear output on compare, set on 0x00 
  
//  T3CCTL1 &= ~BIT6;                     //clear channel1 IM
//  T3CCTL1 |= BIT2;                      //channel1 compare mode
//  T3CCTL1 |= (BIT5 | BIT4);             //(channel1) clear output on compare, set on 0x00                      
  
//  T3CTL |= BIT2;                        //clear TIMER3
  /* **** */
  T3CTL |= BIT4;                        //start TIMER3  
//  while(1);
 
}
