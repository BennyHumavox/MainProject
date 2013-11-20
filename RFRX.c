/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// The program syncs TIMER4 with incoming RF signal and receives an 8 bit word.
// The incoming signal period is limited by TIMER4 step time and by TIMER4 cycle time.
// Timer Step Time = prescaler / (ticks freq.)
// Timer Cycle Time = (Timer Step Time) * 256.
// The program syncs to the incoming signal rising edge and learns the signal's period and DC. to create a PWM signal on P2_3.
// Power of incoming signal is measured using CCA- Clear Channel Assessment. 
// If channel is clear CCA=1, meaning incoming bit is 0.
// If channel is used CCA=0, meaning incoming bit is 1.
//
// Benny Zelman
// 15.01.13
//INCOMPLETE

#include "huma_cc2530_func.c"


#define OUTPUT_POWER                    TRANS_POWER(21)                                                 //transmission power in dBm
#define T1_PRE                          T1_PRE1                                                       //select TIMER1 prescaler 1, 8, 32, 128
#define TIMER_TICKS                     TICKS_FREQ32

/* variables used to capture TIMER value and "learn" incoming signal timing */
unsigned char time1;      //signal first fall time
unsigned char time2;      //signal first rise time
unsigned char time3;      //signal second fall time

void getPWM();          //capture incoming signal rise and fall times
void setPWM();          //set TIMER4 PWM using captured rise and fall times

void main(void)
{
  unsigned char data[3] = {0, 0, 0}, odd_parity = 1, parity_test = 1, sync_on = 0, word_ok = 0; 
  unsigned char i, word_num = 1, data_i = 0;
  
  set32MHzXOSC();
  rfRXConfig();
//  rfTXConfig(FREQ2405, POWER_0DBM);
  CSPT = 0xFF;                          //don't use CSPT
  timerSetup(TIMER_TICKS, T1_PRE);
  timer4Setup();
  clearIRQ();
  
  //CCA related configuration
  CCACTRL0 = 0x42;                                      //set CCA threshold to 0x42 - offset(76dBm) = -10dBm
  CCACTRL1 = ((0xF0 & CCACTRL1) | (0x0F & BIT3));       //set CCA mode '10' with level of hyst. 0 dBm
  
  RFST = ISRXON;                                        //start RX
  //wait 192 microseconds for receiver to get ready
  //wait 8 symbols period (128 microseconds) for RSSI to become valid
  //wait 4 clock periods for CCA update 
  
  getPWM();
  setPWM();
  timer4Setup();
  
  for(data_i = 0; data_i < word_num; data_i++)  //get message loop. word_num==1 by default
  {
    sync_on = getSync();        //wait for sync with transmitter
//    if(!sync_on) //report problem
    for(i=0;i<8;i++)    //get word loop
    {
      if (!(FSMSTAT1 & CCA))         //CCA bit
      {
        data[data_i] = data[data_i] << 1;
        data[data_i]++;
        parity_test ^= 1;
      }
      else
      {
        data[data_i] = data[data_i] << 1;
        parity_test ^= 0;
      }
      //wait for end of period to get next bit
    }
    //parity test
    if (odd_parity == parity_test)
    {
      word_ok = 1;
      if (word_num == 1)        //first word describes message length
      {
        if (data[0] == 0x55) word_num = 2;
        if (data[0] == 0x57) word_num = 3;
      }
    }
    else word_ok = 0;
    //enter parity test info here
    //check if still synced
  }
  
}



void getPWM()
{
  T4CTL |= (BIT7 | BIT6 | BIT5);        //set prescaler to 128
  T4CTL &= ~(BIT1 | BIT0);              //select TIMER4 free run mode
  T4CTL |= BIT4;                        //start counter
  
  while(!(FSMSTAT1 & CCA));            //wait for signal fall (channel is clear)
  time1 = T4CNT;
  while(FSMSTAT1 & CCA);               //wait for signal rise (channel is not-clear)
  time2 = T4CNT;
  while(!(FSMSTAT1 & CCA));            //wait for signal fall (channel is clear)
  time3 = T4CNT;
  
  T4CTL &= ~BIT4;                        //pause counter
 
}

void setPWM()
{
  unsigned char period, dc;
  period = time3 - time1;                //TIMER4 period
  dc = time3 - time2;                    //TIMER4 DC
  
  if(time3 < time1)
  {
    if(time3 < time2)
    {
      period += 0xFF;
      dc += 0xFF;
    }
    else period += 0xFF;
  }
  
  T4CC0 = period;                //TIMER4 period
  T4CC1 = dc;                    //TIMER4 DC
}
