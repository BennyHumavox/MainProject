/*----------------------------------------------------------------------------------------------------------------------------------*/
// This file contains function declarations and definitions for use with CC2530EM.
//
// Benny Zelman
// 03.03.13

#include "huma_cc2530_defs.h"
#include "interrupts.c"


/* public variables */
unsigned char time1 = 0, time2 = 0, time3 = 0;

void rfTXConfig(unsigned char freq, unsigned char power);       //TX register config
void rfRXConfig();                                              //RX register config
void set32MHzXOSC();                                            //set system clock to 32MHz
void timerSetup(unsigned char ticks, unsigned char t1_presclr); //TIMER setup
void timer2Setup();                                             //MAC TIMER setup
void timer4Setup(unsigned char t4_presclr);
void clearIRQ();                                                //reset interrupts, currently only TIMER1
void delay_usec(unsigned char delay_usec);                      //create a delay, input value in microseconds. based on 32MHz clock
void delay_usec2(unsigned char delay_usec);
void rf_prog();                                                 //program CSP
int getSync();                                                  //establish sync
unsigned char getWord();                                        //get transmitted word
signed char getRSSI();                                        //get transmitted RSSI value

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function sets register values for the radio module to operate in TX mode.
// 'freq' is the wanted transmission frequency and 'power' is the output power.
// 'freq' and 'power' values are defined in "power_freq.h"
// registers values are taked from SmartRF Studio.

void rfTXConfig(unsigned char freq, unsigned char power) 
{
  /* RF settings SoC: CC2530 */
  
/* use for cc2531+rf5602 */  
  P0            |= 0x7F; // port 0
  P1            |= 0xEF; // port 1 
  P0DIR         |= 0x80; // port 0 direction 
  P1DIR         |= 0x12; // port 1 direction 
  
  /* use for cc2531+cc2591 */
//  P0            = 0x7F; // port 0
//  P1            = 0xEF; // port 1 
//  P0DIR         = 0x80; // port 0 direction 
//  P1DIR         = 0x12; // port 1 direction 
  
  FRMFILT0      = 0x0D; // frame filtering 
  FRMFILT1      = 0x78; // frame filtering 
  SRCMATCH      = 0x07; // source address matching and pending bits 
  SRCSHORTEN0   = 0x00; // short address matching 
  SRCSHORTEN1   = 0x00; // short address matching 
  SRCSHORTEN2   = 0x00; // short address matching 
  SRCEXTEN0     = 0x00; // extended address matching 
  SRCEXTEN1     = 0x00; // extended address matching 
  SRCEXTEN2     = 0x00; // extended address matching 
  FRMCTRL0      = 0x43; // frame handling 
  FRMCTRL1      = 0x00; // frame handling 
  RXENABLE      = 0x80; // rx enabling 
  RXMASKSET     = 0x00; // rx enabling 
  RXMASKCLR     = 0x00; // rx disabling 
  FREQTUNE      = 0x0F; // crystal oscillator frequency tuning 
  FREQCTRL      = freq; // controls the rf frequency            
  TXPOWER       = power; // controls the output power            
  TXCTRL        = 0x69; // controls the tx settings 
  FSMSTAT0      = 0x3F; // radio status register 
  FSMSTAT1      = 0x2E; // radio status register 
  FIFOPCTRL     = 0x40; // fifop threshold 
  FSMCTRL       = 0x01; // fsm options 
  CCACTRL0      = 0xF8; // cca threshold 
  CCACTRL1      = 0x1A; // other cca options 
  RSSI          = 0x80; // rssi status register 
  RSSISTAT      = 0x00; // rssi valid status register 
  RXFIRST       = 0x00; // first byte in rxfifo 
  RXFIFOCNT     = 0x00; // number of bytes in rxfifo 
  TXFIFOCNT     = 0x00; // number of bytes in txfifo 
  RXFIRST_PTR   = 0x00; // rxfifo pointer 
  RXLAST_PTR    = 0x00; // rxfifo pointer 
  RXP1_PTR      = 0x00; // rxfifo pointer 
  TXFIRST_PTR   = 0x00; // txfifo pointer 
  TXLAST_PTR    = 0x00; // txfifo pointer 
  RFIRQM0       = 0x00; // rf interrupt masks 
  RFIRQM1       = 0x00; // rf interrupt masks 
  RFERRM        = 0x00; // rf error interrupt mask 
  RFRND         = 0x00; // random data 
  MDMCTRL0      = 0x85; // controls modem 
  MDMCTRL1      = 0x14; // controls modem 
  FREQEST       = 0xE4; // estimated rf frequency offset 
  RXCTRL        = 0x3F; // tune receive section 
  FSCTRL        = 0x5A; // tune frequency synthesizer 
  FSCAL0        = 0x24; // tune frequency calibration 
  FSCAL1        = 0x00; // tune frequency calibration 
  FSCAL2        = 0x18; // tune frequency calibration 
  FSCAL3        = 0x2A; // tune frequency calibration 
  AGCCTRL0      = 0x5F; // agc dynamic range control 
  AGCCTRL1      = 0x15; // agc reference level 
  AGCCTRL2      = 0xFE; // agc gain override 
  AGCCTRL3      = 0x2E; // agc control 
  ADCTEST0      = 0x10; // adc tuning 
  ADCTEST1      = 0x0E; // adc tuning 
  ADCTEST2      = 0x03; // adc tuning 
  MDMTEST0      = 0x75; // test register for modem 
  MDMTEST1      = 0x18; // test register for modem 
  DACTEST0      = 0x00; // dac override value 
  DACTEST1      = 0x00; // dac override value 
  DACTEST2      = 0x28; // dac test setting 
  ATEST         = 0x00; // analog test control 
  PTEST0        = 0x00; // override power-down register 
  PTEST1        = 0x00; // override power-down register 
  RFC_OBS_CTRL0 = 0x00; // rf observation mux control 
  RFC_OBS_CTRL1 = 0x00; // rf observation mux control 
  RFC_OBS_CTRL2 = 0x00; // rf observation mux control 
  TXFILTCFG     = 0x09; // tx filter configuration 
  OBSSEL0       = 0x00; // observation output control register 0 
  OBSSEL1       = 0x00; // observation output control register 1 
  OBSSEL2       = 0x00; // observation output control register 2 
  OBSSEL3       = 0x00; // observation output control register 3 
  OBSSEL4       = 0x00; // observation output control register 4 
  OBSSEL5       = 0x00; // observation output control register 5 
  CHVER         = 0x00; // chip version 
  CHIPID        = 0x00; // chip id 

}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function sets register values for the radio module to operate in RX mode.
// registers values are taked from SmartRF Studio
void rfRXConfig()
{
  /* RF settings SoC: CC2530 */
//  P0            = 0xFF; // port 0
//  P1            = 0xFD; // port 1 
//  P0DIR         = 0x80; // port 0 direction 
//  P1DIR         = 0x12; // port 1 direction 
  FRMFILT0      = 0x0C; // frame filtering 
  FRMFILT1      = 0x78; // frame filtering 
  SRCMATCH      = 0x07; // source address matching and pending bits 
  SRCSHORTEN0   = 0x00; // short address matching 
  SRCSHORTEN1   = 0x00; // short address matching 
  SRCSHORTEN2   = 0x00; // short address matching 
  SRCEXTEN0     = 0x00; // extended address matching 
  SRCEXTEN1     = 0x00; // extended address matching 
  SRCEXTEN2     = 0x00; // extended address matching 
  FRMCTRL0      = 0x0C; // frame handling 
  FRMCTRL1      = 0x00; // frame handling 
  RXENABLE      = 0x00; // rx enabling 
  RXMASKSET     = 0x00; // rx enabling 
  RXMASKCLR     = 0x00; // rx disabling 
  FREQTUNE      = 0x0F; // crystal oscillator frequency tuning 
  FREQCTRL      = 0x0B; // controls the rf frequency 
  TXPOWER       = 0xF5; // controls the output power 
  TXCTRL        = 0x69; // controls the tx settings 
  FSMSTAT0      = 0x00; // radio status register 
  FSMSTAT1      = 0x00; // radio status register 
  FIFOPCTRL     = 0x40; // fifop threshold 
  FSMCTRL       = 0x01; // fsm options 
  CCACTRL0      = 0xF8; // cca threshold 
  CCACTRL1      = 0x1A; // other cca options 
  RSSI          = 0x80; // rssi status register 
  RSSISTAT      = 0x00; // rssi valid status register 
  RXFIRST       = 0x00; // first byte in rxfifo 
  RXFIFOCNT     = 0x00; // number of bytes in rxfifo 
  TXFIFOCNT     = 0x00; // number of bytes in txfifo 
  RXFIRST_PTR   = 0x00; // rxfifo pointer 
  RXLAST_PTR    = 0x00; // rxfifo pointer 
  RXP1_PTR      = 0x00; // rxfifo pointer 
  TXFIRST_PTR   = 0x00; // txfifo pointer 
  TXLAST_PTR    = 0x00; // txfifo pointer 
  RFIRQM0       = 0x00; // rf interrupt masks 
  RFIRQM1       = 0x00; // rf interrupt masks 
  RFERRM        = 0x00; // rf error interrupt mask 
  RFRND         = 0x01; // random data 
  MDMCTRL0      = 0x85; // controls modem 
  MDMCTRL1      = 0x14; // controls modem 
  FREQEST       = 0xEB; // estimated rf frequency offset 
  RXCTRL        = 0x3F; // tune receive section 
  FSCTRL        = 0x5A; // tune frequency synthesizer 
  FSCAL0        = 0x24; // tune frequency calibration 
  FSCAL1        = 0x00; // tune frequency calibration 
  FSCAL2        = 0x13; // tune frequency calibration 
  FSCAL3        = 0x2A; // tune frequency calibration 
  AGCCTRL0      = 0x5F; // agc dynamic range control 
  AGCCTRL1      = 0x15; // agc reference level 
  AGCCTRL2      = 0xFE; // agc gain override 
  AGCCTRL3      = 0x2E; // agc control 
  ADCTEST0      = 0x10; // adc tuning 
  ADCTEST1      = 0x0E; // adc tuning 
  ADCTEST2      = 0x03; // adc tuning 
  MDMTEST0      = 0x75; // test register for modem 
  MDMTEST1      = 0x08; // test register for modem 
  DACTEST0      = 0x00; // dac override value 
  DACTEST1      = 0x00; // dac override value 
  DACTEST2      = 0x28; // dac test setting 
  ATEST         = 0x00; // analog test control 
  PTEST0        = 0x00; // override power-down register 
  PTEST1        = 0x00; // override power-down register 
  RFC_OBS_CTRL0 = 0x00; // rf observation mux control 
  RFC_OBS_CTRL1 = 0x00; // rf observation mux control 
  RFC_OBS_CTRL2 = 0x00; // rf observation mux control 
  TXFILTCFG     = 0x09; // tx filter configuration 
  OBSSEL0       = 0x00; // observation output control register 0 
  OBSSEL1       = 0x00; // observation output control register 1 
  OBSSEL2       = 0x00; // observation output control register 2 
  OBSSEL3       = 0x00; // observation output control register 3 
  OBSSEL4       = 0x00; // observation output control register 4 
  OBSSEL5       = 0x00; // observation output control register 5 
  CHVER         = 0x00; // chip version 
  CHIPID        = 0x00; // chip id 
  
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function sets the clock source to 32MHz XOSC
void set32MHzXOSC()
{
//  unsigned char CLK_STA, CLK_CMD;
  //SLEEPCMD = BIT3;              //set system to active/idle mode
  CLKCONCMD = 0x00;             //trigger system clock change to 32MHz XOSC
  
//  CLK_STA = BIT6 & CLKCONSTA;
//  CLK_CMD = BIT6 & CLKCONCMD;
  while(CLKCONSTA != 0);     //wait for 32MHz XOSC to become stable
//  {    
//    CLK_STA = BIT6 & CLKCONSTA;
//    CLK_CMD = BIT6 & CLKCONCMD; 
//  }
  
//  CLKCONCMD = BIT7;             //trigger system clock change
//  while (CLKCONSTA != BIT7);
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function sets operation mode for TIMER1.
// ticks is the counter ticks frequency and t1_presclr is the prescaler value
void timerSetup(unsigned char ticks, unsigned char t1_presclr)  //timer1 setup   
{
   unsigned char CLK_STA, CLK_CMD;
   
  /* tick speed setup */
  CLKCONCMD = (0xC7 & CLKCONCMD) | ticks;
  
  CLK_STA = (BIT5 | BIT4 | BIT3) & CLKCONSTA;
  CLK_CMD = (BIT5 | BIT4 | BIT3) & CLKCONCMD;
  while(CLK_STA != CLK_CMD)        //wait for tick speed to stabilize
  {
    CLK_STA = (BIT5 | BIT4 | BIT3) & CLKCONSTA;
    CLK_CMD = (BIT5 | BIT4 | BIT3) & CLKCONCMD;
  }
  
  /* TIMER1 prescaler */
  T1CTL |= t1_presclr;               //ticks divided by t1_presclr
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function sets operation mode for TIMER2.

void timer2Setup()      //timer2 (MAC) setup
{
  /* set timer period */
//  T2MSEL |= BIT1;       //mux select t2_per register
//  T2M0 = 0x20;          //set low byte of timer period
//  T2M1 = 0x00;          //set high byte of timer period
  //0x20 == 32
  /* end of set timer period */

}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function sets operation mode for TIMER4.
void timer4Setup(unsigned char t4_presclr)      //used to sync. data RX rate
{
//  PERCFG |= BIT4;                       //set TIMER4 peripheral output to alt. 2
//  P2SEL |= (BIT3 | BIT4);               //prioritize TIMER4 over TIMER1 over USART0
//  P2SEL |= BIT2;                        //set P2_3 as peripheral function
  
  T4CTL |= t4_presclr;                  //set prescaler to 128
//  T4CTL |= BIT1;                        //select TIMER4 modulo mode
  
//  T4CCTL1 |= (BIT5 | BIT4);             //clear output on compare, set on 0x00
//  T4CCTL1 |= BIT2;                      //TIMER4 channel1 compare mode
  
 // T4CC0 = ;                //TIMER4 period
 // T4CC1 = ;                //TIMER4 DC
  //
  T4CTL |= BIT2;        //clear counter
  
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function resets interrupt flags and enables interrupts.
// INCOMPLETE
void clearIRQ() //clear IFs and enable IRQ flags for TIMER1
{
  IEN0 &= ~BIT7;                //disable global interrupts
  
  /* clear interrupt flags here */
  
  IEN0 |= BIT7;                 //enable global interrupts
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function gets an integer and holds the CPU for delay_usec microseconds
void delay_usec(unsigned char delay_usec)
{
  //TIMER1 works with tick freq. of 32Mhz and no prescaler
  unsigned char low_d = 0, high_d = 0, mask8 = 0x80, i, T1_IF;
  
  //calculate and assign value to T1CC0H:T1CC0L
//  RFST = ISTXON;
  low_d = delay_usec;
  if(delay_usec)
  {
    if(delay_usec <= 4) low_d = delay_usec << 5;      //no overflow
    else        //overflow
    {
      for(i=0;i<5;i++)
      {
        if(mask8 & low_d)
        {
          if(!high_d) high_d |= 0x01;
          else
          {
            high_d = high_d << 1;
            high_d |= 0x01;
          }
          low_d = low_d << 1;
        }
        else
        {
          if(!high_d) high_d |= 0x01;
          else
          {
            high_d = high_d << 1;
            high_d |= 0x01;
          }
          low_d = low_d << 1;
        }
      }
    }
  }
  T1CC0H = high_d;
  T1CC0L = low_d;
  T1CNTL = 0x00;                //clear TIMER1 value
  T1CCTL0 |= (BIT6 |  BIT2);    //set TIMER1 channel0 IM and compare mode
  
//  RFST = ISRFOFF;
  
//  clearIRQ();
//  T1CTL |= BIT0;                                //start timer1 in free operation mode
  T1CTL |= BIT1;                                //start TIMER1 in modulo mode
  
  T1_IF = T1STAT & BIT0;                        //isolate TIMER1 channel0 IF
  while(!T1_IF) T1_IF = T1STAT & BIT0;          //wait for overflow IF
  
  IEN0 &= ~BIT7;                //disable global interrupts
  
//  T1CNTL = 0x00;                //clear TIMER1 value
  clearIRQ();                   //re-set timers interrupts
}

void delay_usec2(unsigned char delay_usec)
{
}
/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function programs the CSP of the radio module.
// The CSP can run programs of up to 24 instructions.
// Each instruction is written to register RFST in execution order
void rf_prog()
{
//  RFST = LABEL;         //set next instruction as start of loop
//  RFST = SKIP(1,0,5);   //skip 1 instructions if condition 5 (CSPY==0) applies (n=0) 
//  RFST = STXON;         //start TX
//  RFST = WAITX;         //wait for MAC TIMER to overflow no. of times set in CSPX
//  RFST = SRFOFF;        //stop TX/RX
//  RFST = WAIT(31);      //wait for MAC TIMER to overflow 10 times
//  RFST = DECY;          //CSPY--
//  RFST = SKIP(1,1,5);   //skip 1 instructions if condition 5 (CSPY==0) doesn't apply (n=1)
//  RFST = SKIP(0,0,5);   //if(y==0) wait for value of CSPY to update
//  RFST = RPT(0,6);      //goto start of loop if condition 6 (CSPZ==0) applies (n=0)
  
  RFST = LABEL;         //set next instruction as start of loop
  RFST = SKIP(1,0,5);   //skip 1 instructions if condition 5 (CSPY==0) applies (n=0) 
  RFST = STXON;         //start TX
  RFST = WEVENT1;       //wait for TIMER2 event1
  RFST = SRFOFF;        //stop TX/RX
  RFST = WEVENT2;       //wait for TIMER2 event2
  RFST = DECY;          //CSPY--
  RFST = RPT(0,6);      //goto start of loop if condition 6 (CSPZ==0) applies (n=0)
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
// The function syncs TIMER4 to a rising edge of a received signal.
int getSync()
{
  while(!(FSMSTAT1 & CCA));     //wait for falling edge
  while(FSMSTAT1 & CCA);        //wait for rising edge
  T4CTL |= BIT4;
  
  return 1;
}

signed char getRSSI()
{
  signed char oldRSSI[10], lowRSSI; //newRSSI=-127;
  
  for(int i=0;i<10;i++)
  {
    while(!(RSSISTAT & BIT0));                  //wait for RSSI value to become valid
    oldRSSI[i] = RSSI;                             //get RSSI
//    if(oldRSSI == -128)
//    {
//      while(!(RSSISTAT & BIT0));       //check if RSSI value is valid
//      oldRSSI = RSSI;
//    }
//    if(oldRSSI < newRSSI) newRSSI = oldRSSI;
    
    for(long j=0;j<100000;j++) asm("nop");        //delay
  }
  
  lowRSSI = oldRSSI[0];
  for(int k=1;k<10;k++)
  {
    if(oldRSSI[k] < lowRSSI) lowRSSI = oldRSSI[k];
  }
  return lowRSSI;
}
