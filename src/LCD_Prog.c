/******************************************************************/
/*             >>DATE:6/1/2021                                    */
/*             >>AUTHOR:ELSAYED MANSOUR SHALABY                   */
/*             >>VERSION:0.1                                      */
/******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LCD_INT.h"
#include "LCD_config.h"
#include "GPIO_INT.h"
#include "GPIO_Config.h"
#include "SYSTICK_INT.h"
#include "SYSTICK_config.h"



void  LCD_VidInit_8bit(void)
{
    /***********WAIT MORE THAN 30 MS AFTER START***********/
	MSTK_VidSetBusyWait_ms(50);
	/***********SET DIRCETIONS FOR DATA PINS***************/
	MGPIO_VidSetGPIODirection(LCD_DATA_PORT, 0x22222222, LOW_REG);
    /***********SET DIRCETIONS FOR CONTROL PINS************/
	MGPIO_VidSetPinDirection(LCD_CONTROL_PORT,RS_PIN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_CONTROL_PORT,RW_PIN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_CONTROL_PORT,EN_PIN,OUTPUT_SPEED_2MHZ_PP);

	/**************FUNCTION SET COMMAND************************/
	LCD_VidWriteCommand(FUNCTION_SET_8_BIT);
	MSTK_VidSetBusyWait_ms(1);
	/**************DISPLAY ON/OFF COMMAND************************/
	LCD_VidWriteCommand(DISPLAY_OFF_ON);
	MSTK_VidSetBusyWait_ms(1);
	/**************CLEAR DISPLAY COMMAND************************/
    LCD_VidWriteCommand(CLEAR_DISPLAY);
    MSTK_VidSetBusyWait_ms(2);
	/***************ENTRY SET COMMAND*************************/
	LCD_VidWriteCommand(ENTRY_SET);
}
void LCD_VidInit_4bit(void)
{
	 /***********WAIT MORE THAN 30 MS AFTER START***********/
	MSTK_VidSetBusyWait_ms(50);
	/***********SET DIRCETIONS FOR DATA PINS****************/
	MGPIO_VidSetPinDirection(LCD_DATA_PORT,DATA4_LCD,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_DATA_PORT,DATA5_LCD,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_DATA_PORT,DATA6_LCD,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_DATA_PORT,DATA7_LCD,OUTPUT_SPEED_2MHZ_PP);
    /***********SET DIRCETIONS FOR CONTROL PINS************/
	MGPIO_VidSetPinDirection(LCD_CONTROL_PORT,RS_PIN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_CONTROL_PORT,RW_PIN,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(LCD_CONTROL_PORT,EN_PIN,OUTPUT_SPEED_2MHZ_PP);
	/**************FUNCTION SET COMMAND************************/
	LCD_VidWriteCommand(FUNCTION_SET_4_BIT);
	MSTK_VidSetBusyWait_ms(1);
	/**************DISPLAY ON/OFF COMMAND************************/
	LCD_VidWriteCommand(DISPLAY_OFF_ON);
	MSTK_VidSetBusyWait_ms(1);
    /**************CLEAR DISPLAY COMMAND************************/
    LCD_VidWriteCommand(CLEAR_DISPLAY);
    MSTK_VidSetBusyWait_ms(2);
    /***************ENTRY SET COMMAND*************************/
	LCD_VidWriteCommand(ENTRY_SET);
}
	
void LCD_VidWriteCommand(u8 Copy_u8Command)
{
    #if    LCD_MODE   == MODE_8_BITS
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RS_PIN,HIGH);  //RS=0
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);  //RW=0
	/********************WRITE DATA **************************/
	MGPIO_VidSetGPIOValue(LCD_DATA_PORT,Copy_u8Command);
	/********************************************************/
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,HIGH); //EN=1--rising
	MSysTick_VidSetBusyWaitDelay_ms(2);
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,LOW);  //EN=0--falling
     #elif  LCD_MODE   == MODE_4_BITS
	/****************************************************************/
	//u8 Copy_u8Command1=Copy_u8Command&0xf0;//FOR HIGHER BITS
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RS_PIN,LOW);  //RS=0
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);  //RW=0
	/********************WRITE **************************/
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA4_LCD,GET_BIT(Copy_u8Command,4));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA5_LCD,GET_BIT(Copy_u8Command,5));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA6_LCD,GET_BIT(Copy_u8Command,6));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA7_LCD,GET_BIT(Copy_u8Command,7));
   /********************************************************/
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,HIGH); //EN=1--HIGH
	MSTK_VidSetBusyWait_ms(2);
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,LOW);  //EN=0--LOW
	/****************************************************************/
   // Copy_u8Command1=(Copy_u8Command<<4)&0xf0;//FOR LOWER BITS
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RS_PIN,LOW);  //RS=0
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);  //RW=0
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA4_LCD,GET_BIT(Copy_u8Command,0));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA5_LCD,GET_BIT(Copy_u8Command,1));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA6_LCD,GET_BIT(Copy_u8Command,2));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA7_LCD,GET_BIT(Copy_u8Command,3));
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,HIGH); //EN=1--HIGH
	MSTK_VidSetBusyWait_ms(2);
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,LOW);  //EN=0--LOW
	/****************************************************************/
  #endif
}


void LCD_VidWriteData(u8 Copy_u8Data)
{
    #if    LCD_MODE   == MODE_8_BITS
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RS_PIN,HIGH); //RS=1
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);  //RW=0
	/********************WRITE DATA **************************/
	MGPIO_VidSetGpioValue(LCD_DATA_PORT, Copy_u8Data);
	/********************************************************/
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,HIGH); //EN=1--rising
	MSTK_VidSetBusyWait_ms(2);
	MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,LOW);  //EN=0--falling
    #elif  LCD_MODE   == MODE_4_BITS
	/****************************************************************/
    //u8 Copy_u8Data1=Copy_u8Data&0xf0;//FOR HIGHER BITS
   // u8 Copy_u8Data1=Copy_u8Data;
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RS_PIN,HIGH); //RS=1
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);  //RW=0
	/********************WRITE **************************/
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA4_LCD,GET_BIT(Copy_u8Data,4));
	MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA5_LCD,GET_BIT(Copy_u8Data,5));
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA6_LCD,GET_BIT(Copy_u8Data,6));
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA7_LCD,GET_BIT(Copy_u8Data,7));
    /********************************************************/
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,HIGH); //EN=1--HIGH
    MSTK_VidSetBusyWait_ms(2);
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,LOW);  //EN=0--LOW
    /****************************************************************/
    //Copy_u8Data1=(Copy_u8Data<<4)&0xf0;//FOR LOWER BITS
    //Copy_u8Data1=(Copy_u8Data<<4);
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RS_PIN,HIGH); //RS=1
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,RW_PIN,LOW);  //RW=0
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA4_LCD,GET_BIT(Copy_u8Data,0));
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA5_LCD,GET_BIT(Copy_u8Data,1));
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA6_LCD,GET_BIT(Copy_u8Data,2));
    MGPIO_VidSetPinValue(LCD_DATA_PORT,DATA7_LCD,GET_BIT(Copy_u8Data,3));
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,HIGH); //EN=1--HIGH
    MSTK_VidSetBusyWait_ms(2);
    MGPIO_VidSetPinValue(LCD_CONTROL_PORT,EN_PIN,LOW);  //EN=0--LOW
    /****************************************************************/
    #endif


}
void LCD_VidWriteString(u8 *ptr)
{
	for(u8 i=0;ptr[i] != '\0';i++)
	{
		LCD_VidWriteData(ptr[i]);
	}
}
void LCD_VidWriteNumber(u32 LOC_u32num)
{ 	u32 revrese=0;
u8 y;
u8 counter=0;
if(LOC_u32num==0)
{
	LCD_VidWriteData(48);
}
while(LOC_u32num>0)
{
	revrese=(revrese*10)+(LOC_u32num)%10;
	if(revrese==0)
	{
		 y=0;
		 counter++;
	}
	LOC_u32num=LOC_u32num/10;
}
while(revrese>0)
{
	u8 res=revrese%10;
	LCD_VidWriteData(res+48);
	revrese=revrese/10;
}
if(y==0)
{
	for(u8 i=0;i<counter;i++)
	{
		LCD_VidWriteData(48);
	}
}
}

void LCD_GoToXY(u8 row,u8 col)
{
	if(row==0)
	{
		LCD_VidWriteCommand(128+col);
	}
	else if (row==1)
	{
		LCD_VidWriteCommand(192+col);
	}
}
