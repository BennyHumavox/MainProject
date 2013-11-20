/*----------------------------------------------------------------------------------------------------------------------------------*/
// This file contains macro definitions of transmission profiles for use with CC2530EM
//
// Benny Zelman
// 15.01.13

#include "power_freq.h"



/* profiles' settings */
#if P_NUM == 1
#define P_NAME P1

#define P_FC FREQ2401
#define P_MODULATION_NUM 0      //0- NONE. 1- 2FSK, 2- GFSK, 3- MSK 
#define P_HOP_TOGGLE 0          //toggle frequency hopping on/off
#define P_HOP_RANDOM 0          //toggle random hopping on/off
#define P_HOP_START_FREQ FREQ2401
#define P_HOP_END_FREQ FREQ2482
#define P_HOP_STEP 10           //measured in MHz
#define P_HOP_TIME 30           //measured in msec
#define BREAK_ACTIVE 0          //activate breaking mode
#define BREAK_ON 10             //measured in msec
#define BREAK_TIME 20           //measured in msec
#define TIME_SLOT1 1            //measured in min
#define TIME_SLOT2 1            //measured in min
#define TIME_SLOT3 1            //measured in min
#define TIME_SLOT4 1            //measured in min
#define TIME_SLOT5 1            //measured in min
#define TIME_SLOT6 1            //measured in min
#define TIME_SLOT7 1            //measured in min
#define TIME_SLOT8 1            //measured in min
#define TIME_SLOT9 1            //measured in min
#define TIME_SLOT10 1           //measured in min
#define TIME_SLOT11 1           //measured in min
#define TIME_SLOT12 1           //measured in min
#define TIME_SLOT13 1           //measured in min
#define TIME_SLOT14 1           //measured in min
#define TIME_SLOT15 1           //measured in min
#define TIME_SLOT16 1           //measured in min
#define POWER_SLOT1 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT2 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT3 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT4 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT5 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT6 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT7 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT8 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT9 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT10 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT11 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT12 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT13 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT14 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT15 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT16 POWER_9DBM          //measured in dBm [-4,21]

#elif P_NUM == 2
#define P_NAME P2
#define P_FC FREQ2401
#define P_MODULATION_NUM 0      //0- NONE. 1- 2FSK, 2- GFSK, 3- MSK 
#define P_HOP_TOGGLE 0          //toggle frequency hopping on/off
#define P_HOP_RANDOM 0          //toggle random hopping on/off
#define P_HOP_START_FREQ FREQ2401
#define P_HOP_END_FREQ FREQ2482
#define P_HOP_STEP 10           //measured in MHz
#define P_HOP_TIME 30           //measured in msec
#define BREAK_ACTIVE 0          //activate breaking mode
#define BREAK_ON 10             //measured in msec
#define BREAK_TIME 20           //measured in msec
#define TIME_SLOT1 1            //measured in min
#define TIME_SLOT2 1            //measured in min
#define TIME_SLOT3 1            //measured in min
#define TIME_SLOT4 1            //measured in min
#define TIME_SLOT5 1            //measured in min
#define TIME_SLOT6 1            //measured in min
#define TIME_SLOT7 1            //measured in min
#define TIME_SLOT8 1            //measured in min
#define TIME_SLOT9 1            //measured in min
#define TIME_SLOT10 1           //measured in min
#define TIME_SLOT11 1           //measured in min
#define TIME_SLOT12 1           //measured in min
#define TIME_SLOT13 1           //measured in min
#define TIME_SLOT14 1           //measured in min
#define TIME_SLOT15 1           //measured in min
#define TIME_SLOT16 1           //measured in min
#define POWER_SLOT1 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT2 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT3 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT4 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT5 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT6 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT7 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT8 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT9 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT10 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT11 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT12 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT13 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT14 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT15 POWER_9DBM          //measured in dBm [-4,21]
#define POWER_SLOT16 POWER_9DBM          //measured in dBm [-4,21]

#endif


#define TIMESLOT(x) TIME_SLOT##x
#define POWERSLOT(x) POWER_SLOT##x

#if ((P_FC < FREQ2401) || (P_FC > FREQ2482))
#error center frequency is out of range [2401,2482]
#endif
  
#if P_MODUALTION_NUM == 0
#define P_MODUALTION NONE
#elif P_MODUALTION_NUM == 1
#define P_MODUALTION TWO_FSK
#elif P_MODUALTION_NUM == 2
#define P_MODUALTION GFSK
#elif P_MODUALTION_NUM == 3
#define P_MODUALTION MSK
#endif