
#include "huma_cc2530_func.c"

void main (void)
{
   set32MHzXOSC();
  
   P1DIR |= BIT7;                        //P1_7 direction to output
   P1 &= ~BIT7;                          //clear output
  
   APCFG |= (BIT5 | BIT4);      //set P0_4, P0_5 as analog pins
   CMPCTL |= BIT1;              //enable comparator
   
   
   while(1)
   {
     P1 = (BIT7 & (CMPCTL << 7));
   }
}