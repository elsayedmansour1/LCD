#ifndef	GPIO_charERFACE_H
#define	GPIO_charERFACE_H
/*****************************************************************/
		/*PIN NUMBER*/
#define	PIN0		0
#define	PIN1		1
#define	PIN2                2
#define	PIN3                3
#define	PIN4                4
#define	PIN5                5
#define	PIN6                6
#define	PIN7                7
#define	PIN8                8
#define	PIN9                9
#define	PIN10               10
#define	PIN11               11
#define	PIN12               12
#define	PIN13               13
#define	PIN14               14
#define	PIN15               15
/*****************************************************************/

		/*GPIO*/
#define	GPIO_A		0	
#define	GPIO_B		1
#define	GPIO_C		2
/*****************************************************************/

		/*VALUE*/
#define	LOW		0	
#define	HIGH		1
/*****************************************************************/
		/*Select Register*/
#define	HIGH_REG	0
#define LOW_REG		1
#define BOTH_REG	2
/*****************************************************************/
//INPUT
#define INPUT_ANLOG               0b0000
#define INPUT_FLOATING            0b0100
#define INPUT_PULLUP_PULLDOWN     0b1000

//For Speed 10
#define OUTPUT_SPEED_10MHZ_PP     0b0001
#define OUTPUT_SPEED_10MHZ_OD     0b0101
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101

//For Speed 2
#define OUTPUT_SPEED_2MHZ_PP      0b0010
#define OUTPUT_SPEED_2MHZ_OD      0b0110
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110

//For Speed 2
#define OUTPUT_SPEED_50MHZ_PP     0b0011
#define OUTPUT_SPEED_50MHZ_OD     0b0111
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111
  
void MGPIO_VidSetPinDirection	( u8 Copy_u8Port , u8 Copy_u8Pin , u8 u8Copy_u8Mode );
void MGPIO_VidSetPinValue	    (u8 LOC_u8Port,u8 LOC_u8PinNumber,u8 u8Value);
void MGPIO_VidSetGPIODirection	(u8 LOC_u8Port,u64 LOC_u32Value,u8 LOC_u8Register);
void MGPIO_VidSetGPIOValue		(u8 LOC_u8Port,u32 LOC_u32Value);
u8   MGPIO_u8GetPinValue 		(u8 LOC_u8Port,u8 LOC_u8PinNumber);
void MGPIO_u8TogglePinValue   	(u8 LOC_u8Port,u8 LOC_u8PinNumber);
void MGPIO_VidSetPortValue	(u8 LOC_u8Port,u8 LOC_u8Value,u8 LOC_u8Register);





#endif
