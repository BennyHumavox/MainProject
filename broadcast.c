/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program performs simple transmission toggle.
// The function broadcast(on, off) receives 2 integers and runs delay loops.
// Use macro MIN_TO_LOOPS(mins) in order to calculate number of loops required 
// to get delay in full-minutes under current clock ticks freq. and prescaler.
// Use macro MIN_TO_PT_LOOPS(mins) in order to calculate number of loops required for remainder of time (less than a minute).
//
// Benny Zelman
// 15.01.13


#include "huma_cc2530_func.c"


#define OUTPUT_POWER                    TRANS_POWER(21)                                                //transmission power in dBm
#define T1_PRE                          T1_PRESCALER(128)                                                       //select TIMER1 prescaler 1, 8, 32, 128
#define T1_TICKS                        TICKS_FREQ025
#define T1_CYCLE_MSECS                  ((0xFF / TICKS_FREQ) * T1_PRE)                                  //cycle time in milisec
#define MIN_TO_LOOPS(mins)              ((6000 * mins) / T1_CYCLE_MSECS)                                //convert minutes to required TIMER1 cycles             
#define MIN_TO_PT_LOOPS(mins)           (((6000 * mins) % T1_CYCLE_MSECS)*(TICKS_FREQ / T1_PRE))        //convert remaining less-than-a-minute to TIMER1 value


void broadcast(unsigned char on, unsigned char off);                    // on\off sets DC with regard to full TIMER count

void main(void)
{
  set32MHzXOSC();
  rfTXConfig(FREQ2400, OUTPUT_POWER);
//  CSPT = 0xFF;                          //don't use CSPT
  timerSetup(T1_TICKS, T1_PRE);
  
  clearIRQ();
  P0DIR |= 0x8C;                        //P0 BIT2,3,7 are output, BIT1,4,5,6 are input
  P0 |= (BIT2 & BIT3 & BIT7);
  while(1) broadcast(1,0);
  
}

void broadcast(unsigned char on_limit, unsigned char off_limit)
{
  unsigned char T1_IF, on_cnt = 0, off_cnt = 0;
  clearIRQ();
  
  T1CTL |= BIT0;                //start timer1 in free operation mode
  
  //duty cycle timer
  while(on_cnt < on_limit)    //TX on loop                   
  {
    RFST = ISTXON;                  //ISTXON
    T1_IF = T1STAT & BIT5;      //isolate TIMER1 IF
    while(!T1_IF)               //wait for overflow IF
    {
      T1_IF = T1STAT & BIT5;
    }
    IEN0 &= ~BIT7;              //disable global interrupts
    T1STAT &= ~BIT5;
    on_cnt++;
    clearIRQ();
  }
  
  
  while(off_cnt < off_limit)      //broadcast off loop
  {
    RFST = ISRFOFF;               //ISRFOFF
    T1_IF = T1STAT & BIT5;       //isolate TIMER1 IF
    while(!T1_IF)               //wait for overflow IF
    {
      T1_IF = T1STAT & BIT5;
    }
    IEN0 &= ~BIT7;              //disable global interrupts
    T1STAT &= ~BIT5;
    off_cnt++;
    clearIRQ(); 
  }
}
