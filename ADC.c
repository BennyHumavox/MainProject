/*----------------------------------------------------------------------------------------------------------------------------------*/ 
//This program operates the ADC.

#include "huma_cc2530_func.c"

void main(void)
{
  unsigned char convEnd, ADChigh; 
  set32MHzXOSC();
  rfRXConfig();
  CSPT = 0xFF;                          //don't use CSPT
  //  setTimer(TICKS_FREQ025, T1_PRE128);   //250kHz ticks & prescaler of 128 = full timer cycle of 33.554432 seconds
  clearIRQ();
  
  /* ADC setup */
  APCFG |= BIT6;                        //set PO_6 as analog peripheral I/O
  ADCCON1 |= (BIT5 | BIT4);             //set start event to manual using ADCCON1[6]
  ADCCON3 |= (BIT7);                    //set single conversion reference voltage to AVDD5
  
  P1DIR |= BIT7;                        //set P1_7 as output
  
  while(1)
  {
    ADCCON3 |= (BIT2 | BIT1);             //single channel select- AIN7 and start conversion
    convEnd = BIT7 & ADCCON1;
    
    while(!convEnd)  convEnd = BIT7 & ADCCON1;    //wait for conversion to end
    ADChigh = ADCH;
    if(ADChigh > 0x7E) P1 |= BIT7;
    else P1 &= ~BIT7;
  }
  
}