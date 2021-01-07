#ifndef  _SYSTICK_INTERFACE_H
#define  _SYSTICK_INTERFACE_H


void MSTK_VidINIT	(void);

void MSTK_VidSetBusyWait(u32 Copy_u32Ticks);

void MSTK_VidSetBusyWait_ms(u32 Copy_u32Ticks);

void MSTK_VidSetIntervalSingle(u32 Copy_u32Ticks,void (*LocPFunc)(void));

void MSTK_VidSetIntervalPeriodic(u32 Copy_u32Ticks,void (*LocPFunc)(void));

void MSTK_VidStopInterval(void);

u32 MSTK_u32GetTime(void);

u32 MSTK_u32GetReminingTicks(void);






#endif
