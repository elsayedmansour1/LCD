#ifndef  _SYSTICK_PRIVATE_H
#define  _SYSTICK_PRIVATE_H

typedef struct
{
		volatile u32 CTRL;
		volatile u32 LOAD;
		volatile u32 VAL;
		volatile u32 CALIB;
		
}MSYSTICK;

#define	SYSTICK		((volatile MSYSTICK*)0xE000E010)


#define	MSTK_SRC_AHB	0
#define	MSTK_SRC_AHB_8	1

#define 	MSTK_Single	0
#define 	MSTK_Periodic	1

#endif