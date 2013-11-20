/*----------------------------------------------------------------------------------------------------------------------------------*/ 
// This program activates TX on specified frequency and power.
// Transmission is on as long as switch is toggled on, else transmission is not availible.
//
// Benny Zelman
// 15.08.13


#include "huma_cc2530_func.c"

#define RED_LED                         BIT2
#define GREEN_LED                       BIT3
#define BOX                             BIT4
#define PA_POWER                        BIT7

#define OUTPUT_POWER                    TRANS_POWER(21)                          //transmission power in dBm
#define T1_PRE                          T1_PRESCALER(128)
#define T4_PRE                          T4_PRESCALER(128)

int T1_ovf_cnt, T4_ovf_cnt;

void setT1int();                //setup TIMER1 interrupts
void setT4int();                //setup TIMER4 interrupts
void setP0int();                //setup port 0 interrupts
char readPin();                 //read setup pins status
void setupTX(char status);      //setup TX parameters according the external input
void startTX();                 //start transmission 
void stopTX();                  //stop transmission
void freqSweep(char startFreq, char endFreq, char deltaFreq);   //start transmission with frequency sweep

char trans_power = OUTPUT_POWER;
void main(void)
{
//  char test_pin = BIT2 & BIT3;
//  char T1_IF = 0x00;
//  char pinStatus = 0, TXon = 0;
  long int runTime = 0;             //
  char boxOpen = 0;
  
   /* device setup */
  set32MHzXOSC();
  timerSetup(TICKS_FREQ025, T1_PRE);     
  timer4Setup(T4_PRE); 
//  CSPT = 0xFF;
//  PICTL |= BIT7;
  
  P0DIR |= 0x8C;                        //P0 BIT2,3,7 are output, BIT1,4,5,6 are input
//  if (P0 & BOX) P0 = RED_LED;
//  else P0 = GREEN_LED;

  /* interrupt setup */
   setT1int();             //TIMER1 interrupts
   setT4int();             //TIMER4 interrupts
  //void setP0int();       //Port 0 interrupts
  
  while(P0 & BOX);              //wait for box to close before reading setup parameters
  T1_ovf_cnt = 0;               //restart transmitting period after closing the box
//  pinStatus = readPin();
//  setupTX(pinStatus);
  
  IEN0 |= BIT7;                                 //enable global interrupts.
  T1CTL |= BIT0;                                //start timer1 in free running mode
  
//  if (pinStatus == 0x02) runTime = 645;         //total run time is approx. 6 hours
//  else runTime = 18;                            //total run time is approx. 10 minutes
  
  rfTXConfig(FREQ2455, OUTPUT_POWER);
  runTime = 9;
  
  while(T1_ovf_cnt < runTime)       //stop program after XXX hours
  {
    startTX();
    while(!(P0 & BOX) && T1_ovf_cnt < runTime)     //Box is closed 
    {
        freqSweep(FREQ2400, FREQ2405, 5);
    }
    stopTX();
   
    while(P0 & BOX) boxOpen= 1;              //wait for box to close before reading setup parameters
    if (boxOpen == 1 && T1_ovf_cnt < runTime) T1_ovf_cnt = 0; 
  }
  stopTX();
}

void setT1int()         //setup TIMER1 interrupts.
{
  /* enable interrupt on TIMER1 overflow */
  T1STAT &= ~BIT5;                              //clear TIMER1 overflow IF.
  IRCON &= ~BIT1;                               //clear TIMER1 IF
  TIMIF |= BIT6;                                //set TIMER1 overflow IM.
  IEN1 |= BIT1;                                 //set TIMER1 IE.
}

void setT4int()
{
  /* enable interrupt on TIMER4 overflow */
  TIMIF &= ~BIT4;                               //clear TIMER4 overflow IF
  IRCON &= ~BIT4;                               //clear TIMER4 IF
  T4CTL |= BIT3;                                //set TIMER4 overlow IM
  IEN1 |= BIT4;                                 //set TIMER4 IE
}

void setP0int()         //setup port 0 interrupts.
{
  /* enable interrupt on bit4 (Box open\close) */
  //  IEN1 |= BIT5;                                 //Port 0 IE
  //  P0IEN |= BOX;                                 // individual IE
}

char readPin()
{
  /* This function reads the status on input pins P0_1, P0_5, P0_6 
     and returns their value as a byte  */
  char setup = 0;
  
  setup = (P0 & BIT1);
  setup |= (P0 & BIT5);
  setup |= (P0 & BIT6);
  return setup;
}

void setupTX(char status)
{
  /* The function sets transmission settings according to pin status */
  stopTX();               //stop transmission if active
  
  switch (status)
  {
  case 0x00:            //charge a battery
    break;
  case 0x02:            //longevity test
    rfTXConfig(FREQ2445, trans_power);
    break;
  case 0x20:
    rfTXConfig(FREQ2445, TRANS_POWER(10));
    break;
  case 0x22:            //frequency sweep
    break;
  case 0x40:            // charge 2 hearing aid devices
    rfTXConfig(FREQ2415, TRANS_POWER(11));
    break;
  case 0x42:
    rfTXConfig(FREQ2480, trans_power);
    break;
  case 0x60:
    rfTXConfig(FREQ2445, TRANS_POWER(8));
    break;
  case 0x62:            //default setting for 3 positions of HA
    rfTXConfig(FREQ2445, trans_power);
    break;    
  }
}

void startTX()
{
  P0 |= PA_POWER;
//  P0 &= ~RED_LED;
  P0 &= ~GREEN_LED;
  RFST = ISTXON;
//  P0 |= GREEN_LED;
  P0 |= RED_LED;
}

void stopTX()
{
  RFST = ISRFOFF;
  P0 &= ~PA_POWER;
//  P0 &= ~GREEN_LED;
   P0 &= ~RED_LED;
//  P0 |= RED_LED;
   P0 |= GREEN_LED;
}

void freqSweep(char startFreq, char endFreq, char deltaFreq)
{
  char freqNo = (endFreq - startFreq)/deltaFreq;        //number of frequency sweep points
  stopTX(); 
  for (char i = 0; (i < freqNo) && !(P0 & BOX); i++)
  {
    rfTXConfig(startFreq, trans_power);     //set TX parameters
    T4CTL |= BIT4;                              //start timer4 operation
    startTX();                                  //start TX
    while (!(P0 & BOX) & T4_ovf_cnt < 4);      //wait 2 seconds for each frequency
    T4CTL &= ~BIT4;                             //pause timer4 operation
    T4_ovf_cnt = 0;
    stopTX();           
    startFreq += deltaFreq;                     //move to next frequency
  }    
}