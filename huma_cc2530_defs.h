/*----------------------------------------------------------------------------------------------------------------------------------*/
// This file contains macros definitions of ticks frequency and prescaler values for use with CC2530EM.
//
// Benny Zelman
// 15.01.13

#include <hal_board_cfg.h>
#include <mac_radio_defs.h>
#include <hal_mac_cfg.h>
#include <hal_types.h>
#include <hal_defs.h>
//#include <basic_rf.h>
#include <iocc2531.h>
#include "huma_cc2530_csp_defs.h"


#define P_NUM 1                 //set profile no. to use
#define DEFAULT_P_NUM 1         //set default profile number 


#include "tx_profiles.h"

#define TICKS_FREQ32 XOSC_TICK_FREQ(32)
#define TICKS_FREQ16 XOSC_TICK_FREQ(16)
#define TICKS_FREQ8 XOSC_TICK_FREQ(8)
#define TICKS_FREQ4 XOSC_TICK_FREQ(4)
#define TICKS_FREQ2 XOSC_TICK_FREQ(2)
#define TICKS_FREQ1 XOSC_TICK_FREQ(1)
#define TICKS_FREQ05 XOSC_TICK_FREQ(05)
#define TICKS_FREQ025 XOSC_TICK_FREQ(025)

