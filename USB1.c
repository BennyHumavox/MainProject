/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program controls selected pin output.
// Use for testing purposes.
//
// Benny Zelman
// 17.02.13


#include "huma_cc2530_func.c"

#define T1_PRE                          T1_PRE128                                                       //select TIMER1 prescaler 1, 8, 32, 128
#define T1_TICKS                        TICKS_FREQ2

void main(void)
{
  unsigned char stage_no = 1, stage_cnt = 0, T1_IF;
  set32MHzXOSC();
  timerSetup(T1_TICKS, T1_PRE);
    
  /* selected output pin */
  //P1SEL |= BIT7;                        //use P1_7 as peripheral function
  P1DIR |= (BIT1);                        //P1_1 direction to output
  P1 &= ~(BIT1| BIT0);                          //clear output
  
  
  clearIRQ();
  while(1)
  {
    T1CTL |= BIT0;                        //start TIMER1 in free operation mode
    /* 10 seconds wait*/
    for(int i=0;i<5;i++)
    {
      T1_IF = T1STAT & BIT5;      //isolate TIMER1 IF
      while(!T1_IF)               //wait for overflow IF
      {
        T1_IF = T1STAT & BIT5;
      }
      clearIRQ();
    }
    T1CTL &= ~(BIT1 | BIT0);            //stop TIMER1
    T1CNTL = 0x00;                      //clear TIMER1
    clearIRQ();
    
    for(stage_cnt=0;stage_cnt<2*stage_no;stage_cnt++)
    {
      T1CTL |= BIT0;                        //start TIMER1 in free operation mode
      /* set output */
      P1 ^= (BIT1 | BIT0);
      
      T1_IF = T1STAT & BIT5;      //isolate TIMER1 IF
      while(!(T1STAT & BIT5));               //wait for overflow IF

      T1CTL &= ~(BIT1 | BIT0);            //stop TIMER1
      T1CNTL = 0x00;                      //clear TIMER1
      clearIRQ();
     
    }
    
    if(stage_no == 5) stage_no = 1;
    else stage_no++;
    
    T1CTL &= ~(BIT1 | BIT0);            //stop TIMER1
    T1CNTL = 0x00;                      //clear TIMER1
    clearIRQ();
  }  
}

  
