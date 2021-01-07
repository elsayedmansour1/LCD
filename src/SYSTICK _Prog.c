/******************************************************************/
/*             >>DATE:8/12/2020                                  */
/*             >>AUTHOR:ELSAYED MANSOUR SHALABY                   */
/*             >>VERSION:0.1                                      */
/******************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"SYSTICK_INT.h"
#include"SYSTICK_Priv.h"
#include"SYSTICK_Config.h"

static void (*MSTK_CallBack) (void)=NULL;
static	u8 MSTK_u8ModeOfInterval=0;
void MSTK_VidINIT	(void)
{
	#if	MSTK_CLK_SRC==MSTK_SRC_AHB
		SET_BIT(SYSTICK->CTRL,2);

	#elif	MSTK_CLK_SRC==MSTK_SRC_AHB_8
		CLR_BIT(SYSTICK->CTRL,2);
	#else	#error"Wrong Choose	Prescaler"
	#endif

}
void MSTK_VidSetBusyWait(u32 Copy_u32Ticks)
{
	/*load ticks to LOAD Register*/
	SYSTICK->LOAD=Copy_u32Ticks;
	/*Start count*/
	SET_BIT(SYSTICK->CTRL,0);
	/*Wait Till Flag Is Rising*/
	while(GET_BIT(SYSTICK->CTRL,16)==0);
	/*Stop Timer*/
	CLR_BIT(SYSTICK->CTRL,0);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=0;
}
void MSTK_VidSetBusyWait_ms(u32 Copy_u32Ticks)
{
	/*load ticks to LOAD Register*/
	SYSTICK->LOAD=(Copy_u32Ticks*1000);
	/*Start count*/
	SET_BIT(SYSTICK->CTRL,0);
	/*Wait Till Flag Is Rising*/
	while(!GET_BIT(SYSTICK->CTRL,16));
	/*Stop Timer*/
	CLR_BIT(SYSTICK->CTRL,0);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=0;
}
void MSTK_VidSetIntervalSingle(u32 Copy_u32Ticks,void (*LocPFunc)(void))
{
	/*load ticks to LOAD Register*/
	SYSTICK->LOAD=Copy_u32Ticks;
	/*Start count*/
	SET_BIT(SYSTICK->CTRL,0);
	/*Call Back*/
	MSTK_CallBack=LocPFunc;
	/*Set mode to Single*/
	MSTK_u8ModeOfInterval=MSTK_Single;
	/*Enable SYSTIC Interrupt*/
	SET_BIT(SYSTICK->CTRL,1);
}
void MSTK_VidSetIntervalPeriodic(u32 Copy_u32Ticks,void (*LocPFunc)(void))
{
	/*load ticks to LOAD Register*/
	SYSTICK->LOAD=Copy_u32Ticks;
	/*Start count*/
	SET_BIT(SYSTICK->CTRL,0);
	/*Call Back*/
	MSTK_CallBack=LocPFunc;
	/*Set mode to Periodic*/
	MSTK_u8ModeOfInterval=MSTK_Periodic;
	/*Enable SYSTIC Interrupt*/
	SET_BIT(SYSTICK->CTRL,1);
}
void MSTK_VidStopInterval(void)
{
	/*Stop count*/
	CLR_BIT(SYSTICK->CTRL,0);
	/*Stop Timer*/
	CLR_BIT(SYSTICK->CTRL,0);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=0;	
}

u32 MSTK_u32GetTime(void)
{
	u32 Loc_u32Time=0;
	
	Loc_u32Time=(SYSTICK->LOAD - SYSTICK->VAL);
	
	return Loc_u32Time;
}
u32 MSTK_u32GetReminingTicks(void)
{
	u32 Loc_u32ReminingTime=0;
	
	Loc_u32ReminingTime=(SYSTICK->VAL);
	return Loc_u32ReminingTime;
}
void SysTick_Handler(void)
{
	u8 Loc_u8Temp=0;
	if(MSTK_u8ModeOfInterval==MSTK_Single)
	{
		/*Stop count*/
	CLR_BIT(SYSTICK->CTRL,0);
	/*Stop Timer*/
	CLR_BIT(SYSTICK->CTRL,0);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=0;	
	}
	/*CallBack Function "Notification"*/
	MSTK_CallBack();
	/*Clear Flag*/
	Loc_u8Temp=GET_BIT(SYSTICK->CTRL,16);

}
