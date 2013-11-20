/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// Test program for PCB bring up procedure.
// This program toggles each GPIO pins one after another for a period of time set by TIMER1.
// 
//
// Benny Zelman
// 09.07.13


#include "huma_cc2530_func.c"

#define RED_LED                         BIT3
#define GREEN_LED                       BIT2
#define BOX                             BIT4

#define OUTPUT_POWER                    TRANS_POWER(10)                                                //transmission power in dBm

char T1_ovf_cnt;

void main(void)
{
//  char test_pin = BIT2 & BIT3;
//  char T1_IF = 0x00;
 
  /* device setup */
  set32MHzXOSC();
  rfTXConfig(FREQ2450, OUTPUT_POWER);
  timerSetup(TICKS_FREQ8, T1_PRE8);     
 
  
  CSPT = 0xFF;
//  PICTL |= BIT7;
  
//  P0SEL = 0x00;
  P0DIR |= 0x0C;                        //P0 BIT2,3 are output, BIT4 is input
  P0 = GREEN_LED;
//  P0 |= test_pin;
  
  /* interrupt setup */
  //TIMER1
  T1STAT &= ~BIT5;                              //clear TIMER1 overflow IF.
  IRCON &= ~BIT1;                               //clear TIMER1 IF
//  TIMIF |= BIT6;                                //set TIMER1 overflow IM.
//  IEN1 |= BIT1;                                 //set TIMER1 IE.
  
   
  //Port 0
  IEN1 |= BIT5;                                 //Port 0 IE
  P0IEN |= BOX;                                 // individual IE
  
  
  
  IEN0 |= BIT7;                                 //enable global interrupts.
  T1CTL |= BIT0;                                //start timer1 in free running mode
  
  
//  P0 ^= 0xFF;
  
  while(1)
  {
   
//    T1_IF = T1STAT & BIT5;
//    while(!(T1STAT & BIT5));
//    {
//      T1_IF = T1STAT & BIT5;
//    }
//    if (P0 & BOX) P0 = GREEN_LED;
//    else P0 = RED_LED;
    
//    IEN0 &= ~BIT7;                                //disable global interrupts
//    T1STAT &= ~BIT5;
//    IRCON &= ~BIT1;                               //clear TIMER1 IF


//      T1_IF = IRCON & BIT1;
//      while (!T1_IF)
//      {
//        T1_IF = IRCON & BIT1;
//      }
//      IEN0 &= ~BIT7;
//      IRCON &= ~BIT1;
      
//    P0 ^= 0xFF;
//    P0 = ~P0;
//   IEN0 |= BIT7;                                 //enable global interrupts.
//     RFST = ISTXON;
    
  }
}

