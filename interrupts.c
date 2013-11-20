#define iGREEN_LED       (1 << 2)
#define iRED_LED         (1 << 3)
#define iBOX             (1 << 4)

/* global variables */
extern int T1_ovf_cnt = 0;
extern int T4_ovf_cnt = 0;
extern int TXFreq = 0;


////RF core interrupt vector
//#pragma vector = 0x83
//__interrupt void RF_ISR(void) 
//{
//  
//}

//TIMER1 interrupt vector
#pragma vector = 0x4B
__interrupt void T1_ISR(void)
{
  IEN0 &= ~BIT7;                        //disable global interrupts
  T1_ovf_cnt++;
  T1STAT &= ~BIT5;                      //clear TIMER1 overflow IF
  IRCON &= ~BIT1; 
  IEN0 |= BIT7;                         //enable global interrupts
}

//TIMER4 interrupt vector
#pragma vector = 0x63
__interrupt void T4_ISR(void)
{
  IEN0 &= ~BIT7;                        //disable global interrupts
  T4_ovf_cnt++;
  TIMIF &= ~BIT4;                       //clear TIMER4 overflow IF
  IRCON &= ~BIT4;                       //clear TIMER4 IF
  IEN0 |= BIT7;                         //enable global interrupts
}

//P0 interrupt vector
#pragma vector = 0x6B
__interrupt void P0_ISR(void)
{
  /* currently handles only P0_4 interrupt */
  IEN0 &= ~BIT7;                //disable global interrupts
  
  if (P0IFG & BIT4)             //BIT4 interrupt
  {
    RFST = ISRFOFF;             //stop TX
    if (TXFreq <= (FREQ2507 - 4))
    {
      TXFreq += 4;                //increase TX frequency by 4MHz    
    }
    else 
    {
      if (TXFreq == FREQ2507) TXFreq = FREQ2395;
      else TXFreq = FREQ2507;
    }
    FREQCTRL = TXFreq;
    RFST = ISTXON;
    P0IFG = ~iBOX;                //clear BIT4 IF
  }
  
  IRCON &= ~BIT5;                //clear P0 IF
  IEN0 |= BIT7;                 //enable general interrupts
}

//P1 interrupt vector
//#pragma vector = 0x7B
//__interrupt void P1_ISR(void)
//{
//}
//
////P2 interrupt vector
//#pragma vector = 0x33
//__interrupt void P2_ISR(void)
//{
//}