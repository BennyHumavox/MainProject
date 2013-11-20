/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program handles an interrupt from an exteranl device on selected pin.
// Future use will be to use an envelope detector as the external device.
//
// Benny Zelman
// 03.03.13


#include "huma_cc2530_func.c"

void main (void)
{
  set32MHzXOSC();
  
  P0IFG &= ~BIT4;               //clear P0_4 IF
  IRCON &= ~BIT5;               //clear P0 IF;
  PICTL &= ~BIT0;               //configure P0 interrupt request on rising edge
  P0IEN |= BIT4;                //enable P0_4 IM
  IEN1 |= BIT5;                 //enable P0 interrupts
  
  clearIRQ();
  
  IEN0 &= ~BIT7;                //disable global interrupts
  P1DIR |= BIT7;                //set P1_7 as output pin
  P1 &= ~BIT7;
 
  while(!(P0IFG & BIT4));
  P1 |= BIT7;
  for(long i=0;i<1000000;i++);
  P1 &= ~BIT7;
  while(1);
}

