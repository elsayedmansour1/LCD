#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H



void LCD_VidInit_8bit(void);
void LCD_VidInit_4bit(void);
void LCD_VidWriteCommand(u8 Copy_u8Data);
void LCD_VidWriteData(u8 Copy_u8Data);
void LCD_VidWriteString(u8 *ptr);
void LCD_GoToXY(u8 row,u8 col);
void LCD_VidWriteNumber(u32 LOC_u32num);

#define     FUNCTION_SET_8_BIT                        0b00111000 //DL=1 --->8 BIT MODE
#define     FUNCTION_SET_4_BIT                        0b00101000 //DL=0 --->4 BIT MODE
#define     CLEAR_DISPLAY                             0b00000001
#define     DISPLAY_OFF_ON                            0b00001110
#define     ENTRY_SET                                 0b00000001




#endif

