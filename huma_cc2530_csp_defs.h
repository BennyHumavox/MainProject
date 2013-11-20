/*----------------------------------------------------------------------------------------------------------------------------------*/
// This file contains macro definitions for the CC2530EM CSP.
//
// Benny Zelman
// 15.01.13


#define SKIP(s,n,c)     (0x00 | ((0x07 & (s)) << 4) | ((0x01 & (n)) << 3) | (0x07 & (c)))
#define WEVENT1         0xB8
#define WEVENT2         0xB9
#define INT             0xBA
#define LABEL           0xBB
#define WAITX           0xBC
#define INCY            0xC1
#define DECY            0xC4
#define SRXON           0xD3
#define STXON           0xD9
#define SSAMPLECCA      0xDB
#define SRFOFF          0xDF
#define WAIT(w)         (0x80 | ((w) & 0x1F))
#define RPT(n,c)        (0xA0 | ((0x01 & (n)) << 3) | ((c) & 0x0F))
#define ISSTART         0xE1
#define ISSAMPLECCA     0xEB
