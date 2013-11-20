/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program programs the CSP to start and stop transmission for defined periods of time using MAC TIMER.
// It will be used to test communication protocol by transmitting a 2-bit sync word followed by an 8-bit word.
// sync word = '01', default word = '0xFF'
// Benny Zelman
// 17.01.13
//INCOMPLETE

#include "huma_cc2530_func.c"


#define OUTPUT_POWER                    TRANS_POWER(21)                                                 //transmission power in dBm
#define T1_PRE                          T1_PRE1                                                       //select TIMER1 prescaler 1, 8, 32, 128
#define TIMER_TICKS                     TICKS_FREQ32
#define WORD_LEN                        8

void main(void)
{
  unsigned char tmp = 0;
  
  IEN0 &= ~BIT7;                //disable global interrupts
  set32MHzXOSC();
  rfTXConfig(FREQ2405, POWER_0DBM);
  
  CSPZ = 0x00;
  CSPY = 0x02;
  CSPX = 0x10;
  CSPT = 0xFF;
  CSPCTRL = 0x01;
  rf_prog();
  
 
  IEN0 &= ~BIT7;                //disable global interrupts
  
  /* clear RF IF */
  RFIRQF1 &= ~BIT5;             //clear CSP_WAIT IF
  S1CON = 0x00;                 //clear general RF IF
  
//  RFIRQF1 &= ~BIT4;             //clear CSP_STOP IF
  /* end RF IF setup */
  
  T2IRQF &= ~BIT0;      //clear TIMER overflow IF
  T2IRQM |= BIT3;       //enable TIMER2 overflow IM
  T2IRQM |= BIT0;       //enable TIMER2 IM 
  IEN1 |= BIT2;         //enable TIMER2 interrupt
  
  /* set RF IM */
  IEN2 |= BIT0;         //set RF general IM
  RFIRQM1 |= BIT5;      //set CSP_WAIT IM
//  RFIRQM1 &= BIT4;      //set CSP_STOP IM

  /* end RF IM setup */

  
  
//  CSPZ = 0x00;
//  CSPY = 0x02;
//  CSPX = 0x10;
//  CSPCTRL = 0x01;
  
//  T2MSEL |= (BIT1);             //mux select T2_PER
//  T2M0 = 0x00;                  //set low byte of T2_PER
//  T2M1 = 0x01;                  //set high byte of T2_PER
  T2MSEL = 0x00;                
  
  T2CTRL |= BIT1;               //start of TIMER2 is synced with 32MHz clock
  T2CTRL |= BIT0;               // start TIMER2 operation
  
  while(T2CTRL & BIT2);
  while(1)
  {
    //timer2Setup();
    if(!tmp)
    {
      RFST = ISSTART;           // start CSP program execution
      
      tmp++;
    }
    if(RFST);
    if(!CSPX) CSPX = 0x10;
    if(!CSPY) CSPY = 0x02;
    
  }
}

