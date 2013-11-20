/*----------------------------------------------------------------------------------------------------------------------------------*/
// This file contains macro definitions for frequency and power transmission for use with CC2530EM
//
// Benny Zelman
// 15.01.13


/* bits */
#define BIT0 1
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)

/* Power conversion from dBm to TXPOWER register value */
#define POWER_MIN4DBM   0x05
#define POWER_MIN2DBM   0x15
#define POWER_0DBM      0x25
#define POWER_1DBM      0x35
#define POWER_2DBM      0x40
#define POWER_3DBM      0x4F
#define POWER_4DBM      0x45
#define POWER_6DBM      0x55
#define POWER_8DBM      0x5D
#define POWER_9DBM      0x65
#define POWER_10DBM     0x6D
#define POWER_11DBM     0x75
#define POWER_12DBM     0x7D
#define POWER_13DBM     0x85
#define POWER_14DBM     0x95
#define POWER_15DBM     0xA0
#define POWER_16DBM     0xA5
#define POWER_17DBM     0xB5
#define POWER_18DBM     0xC5
#define POWER_19DBM     0xD5
#define POWER_20DBM     0xE5
#define POWER_21DBM     0xF5
#define POWERMAX        0xFF    

/*frequency conversion from MHz to FREQCTRL register value */
#define FREQ2395 0x01
#define FREQ2400 0x06        
#define FREQ2401 0x07
#define FREQ2405 0x0B
#define FREQ2410 0x10
#define FREQ2415 0x15
#define FREQ2420 0x1A
#define FREQ2430 0x24
#define FREQ2435 0x29
#define FREQ2440 0x2E
#define FREQ2445 0x33
#define FREQ2450 0x38
#define FREQ2455 0x3C
#define FREQ2460 0x42
#define FREQ2470 0x4C
#define FREQ2475 0x51
#define FREQ2480 0x56
#define FREQ2482 0x58
#define FREQ2485 0x5B
#define FREQ2490 0x60
#define FREQ2495 0x65
#define FREQ2500 0x6A
#define FREQ2505 0x6F
#define FREQ2507 0x71

#define TICKS32 (0x00)
#define TICKS16 (BIT3)
#define TICKS8 (BIT4)
#define TICKS4 (BIT4 | BIT3)
#define TICKS2 (BIT5)
#define TICKS1 (BIT5 | BIT3)
#define TICKS05 (BIT5 | BIT4)
#define TICKS025 (BIT5 | BIT4 | BIT3)

#define T1_PRESCAL1 0x00
#define T1_PRESCAL8 BIT2
#define T1_PRESCAL32 BIT3
#define T1_PRESCAL128 (BIT3 | BIT2)

#define T4_PRESCAL1     0x00
#define T4_PRESCAL2     (BIT5)
#define T4_PRESCAL4     (BIT6)
#define T4_PRESCAL8     (BIT6 | BIT5)
#define T4_PRESCAL16    (BIT7)
#define T4_PRESCAL32    (BIT7 | BIT5)
#define T4_PRESCAL64    (BIT7 | BIT6)
#define T4_PRESCAL128   (BIT7 | BIT6 | BIT5)

#define TRANS_NPOWER(pow) POWER_MIN##pow##DBM
#define TRANS_POWER(pow) POWER_##pow##DBM
#define XOSC_TICK_FREQ(ticker) TICKS##ticker
#define T1_PRESCALER(prescaler1) T1_PRESCAL##prescaler1
#define T4_PRESCALER(prescaler4) T4_PRESCAL##prescaler4
