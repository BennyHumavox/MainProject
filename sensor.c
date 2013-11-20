/*----------------------------------------------------------------------------------------------------------------------------------*/ 
//This program uses CCA to implement a power level detection sensor.
//Detection threshold is set in register CCACTRL0 and is given in 2s complement.
//Threshold value on the CC2530 is offset by 76dBm.

#include "huma_cc2530_func.c"

void main(void)
{
  unsigned char newCCA;
//  unsigned long bitcount = 0, oldCCA, T1ovf = 0;
  signed tmpCCA;
  
  set32MHzXOSC();
  rfRXConfig();
  CSPT = 0xFF;                          //don't use CSPT
  timerSetup(TICKS_FREQ025, T1_PRE128);   //250kHz ticks & prescaler of 128 = full timer cycle of 33.554432 seconds
  clearIRQ();
  RFST = ISRXON;
  
  /* TIMER1 interrupt setup */
  T1STAT &= ~BIT5;                      //clear TIMER1 overflow IF
  TIMIF |= BIT6;                        //set TIMER1 overflow IM
  IEN1 |= BIT1;                         //set TIMER1 interrupt enable
  IEN0 |= BIT7;                         //enable general interrupts
  
  /* CCA setup */
  
  tmpCCA = getRSSI();
//  CCACTRL0 = tmpCCA;
  CCACTRL0 = tmpCCA + 0x01;             //set CCA threshold to (tmpCCA - 76 + 1)[dBm]
//  CCACTRL0 = 0x36;
  CCACTRL1 |= (BIT4 | BIT3);    //CCA operation mode select
  CCACTRL1 &= ~(0x07);          //clear CCA hysteresis
  
  P1DIR |= 0xFF;                //set P1 pins as output
 
  newCCA = 0;
//  oldCCA = 0;
//  T1CTL |= BIT0;                //start TIMER1 in free running mode
  while(1)
  {
    
    while(!(RSSISTAT & BIT0));    //wait for RSSI valid
    /* 4 clock cycles for CCA to stablize after RSSI becomes valid */
//    asm("nop");
//    asm("nop");
//    asm("nop");
//    asm("nop");
    RFST = ISSAMPLECCA;            //sample current calue of CCA  
    newCCA = BIT3 & FSMSTAT1;      //save sampled CCA status bit
    
    if(!newCCA) P1 |= 0x40;
    else P1 &= ~BIT6;                   //output CCA state to pin

/* this part will be used to find signal period */    
//    if(newCCA && !oldCCA) bitcount++;    //count number of pulses
//    oldCCA = newCCA;
//    if(T1STAT & BIT5) T1ovf++;
//    if(T1ovf==2)                        //calculate signal period using known time of 2 TIMER1 full cycles
//    {
//      T1CTL &= ~BIT0;        //stop TIMER1 operation
//      period = bitcount / 67108;
//    }
    
  }
}
