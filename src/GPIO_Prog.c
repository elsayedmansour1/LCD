/******************************************************************/
/*             >>DATE:6/12/2020                                  */
/*             >>AUTHOR:ELSAYED MANSOUR SHALABY                   */
/*             >>VERSION:0.2                                      */
/******************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"GPIO_INT.h"
#include"GPIO_Priv.h"
#include"GPIO_Config.h"


void MGPIO_VidSetPinDirection( u8 Copy_u8Port , u8 Copy_u8Pin , u8 u8Copy_u8Mode )
{

	switch(Copy_u8Port){
	case GPIO_A:

		if(Copy_u8Pin <= 7 ){//low

			GPIOA->CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ));// R M W
			GPIOA->CRL |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 );

		}else if(Copy_u8Pin <=15 ){//high

			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOA->CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
			GPIOA->CRH |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 );
		}

		break;

	case GPIO_B:

		if(Copy_u8Pin <= 7 ){//low

			GPIOB->CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );// R M W
			GPIOB->CRL |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;

		}else if(Copy_u8Pin <=15 ){//high

			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOB->CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
			GPIOB->CRH |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
		}

		break;
	case GPIO_C:

		if(Copy_u8Pin <= 7 ){//low

			GPIOC->CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );// R M W
			GPIOC->CRL |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;

		}else if(Copy_u8Pin <=15 ){//high

			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOC->CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
			GPIOC->CRH |= ( u8Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
		}

		break;
	default :break;
	}

}
void MGPIO_VidSetPinValue (u8 LOC_u8Port,u8 LOC_u8PinNumber,u8 LOC_u8Value)
{
	if(LOC_u8PinNumber<16)
	{
		if(LOC_u8Value==HIGH)
		{
		switch(LOC_u8Port)
		{
		case GPIO_A :GPIOA->BSRR=(1<<LOC_u8PinNumber);break;
		case GPIO_B :GPIOB->BSRR=(1<<LOC_u8PinNumber);break;
		case GPIO_C :GPIOC->BSRR=(1<<LOC_u8PinNumber);break;
		}	
		}
		else if(LOC_u8Value==LOW)
		{
		switch(LOC_u8Port)
		{
		case GPIO_A :GPIOA->BRR=(1<<LOC_u8PinNumber);break;
		case GPIO_B :GPIOB->BRR=(1<<LOC_u8PinNumber);break;
		case GPIO_C :GPIOB->BRR=(1<<LOC_u8PinNumber);break;
		}	
		}
	
	}
	
}
u8	 MGPIO_u8GetPinValue (u8 LOC_u8Port,u8 LOC_u8PinNumber)
{
u8 return_value=0;
		switch(LOC_u8Port)
		{
		case GPIO_A :return_value=GET_BIT(GPIOA->IDR,LOC_u8PinNumber);break;
		case GPIO_B :return_value=GET_BIT(GPIOB->IDR,LOC_u8PinNumber);break;
		case GPIO_C :return_value=GET_BIT(GPIOC->IDR,LOC_u8PinNumber);break;
		}
return return_value;		
}

void MGPIO_u8TogglePinValue   	(u8 LOC_u8Port,u8 LOC_u8PinNumber)
{
	switch(LOC_u8Port)
	{
	case GPIO_A :TOG_BIT(GPIOA->ODR,LOC_u8PinNumber);break;
	case GPIO_B :TOG_BIT(GPIOB->ODR,LOC_u8PinNumber);break;
	case GPIO_C :TOG_BIT(GPIOC->ODR,LOC_u8PinNumber);break;
	}
}

void MGPIO_VidSetGPIODirection	(u8 LOC_u8Port,u64 LOC_u32Value,u8 LOC_u8Register)
{
	if (LOC_u8Register==HIGH_REG)
	{
		switch(LOC_u8Port)
		{
		case GPIO_A :GPIOA->CRH=LOC_u32Value;break;
		case GPIO_B :GPIOB->CRH=LOC_u32Value;break;
		case GPIO_C :GPIOC->CRH=LOC_u32Value;break;
		}
	}
	else if(LOC_u8Register==LOW_REG)
	{
		switch(LOC_u8Port)
		{
		case GPIO_A :GPIOA->CRL=LOC_u32Value;break;
		case GPIO_B :GPIOB->CRL=LOC_u32Value;break;
		case GPIO_C :GPIOC->CRL=LOC_u32Value;break;
		}
	}
	else if(LOC_u8Register==BOTH_REG)
	{
		switch(LOC_u8Port)
		{
		case GPIO_A :GPIOA_CR=LOC_u32Value;break;
		case GPIO_B :GPIOB_CR=LOC_u32Value;break;
		case GPIO_C :GPIOC_CR=LOC_u32Value;break;
		}
	}

}

void MGPIO_VidSetGPIOValue	(u8 LOC_u8Port,u32 LOC_u32Value)
{
	switch(LOC_u8Port)
	{
	case GPIO_A :GPIOA->ODR=LOC_u32Value;break;
	case GPIO_B :GPIOB->ODR=LOC_u32Value;break;
	case GPIO_C :GPIOC->ODR=LOC_u32Value;break;
	}
}
void MGPIO_VidSetPortValue	(u8 LOC_u8Port,u8 LOC_u8Value,u8 LOC_u8Register)
{
	if (LOC_u8Register==HIGH_REG)
	{
		switch(LOC_u8Port)
		{
		case GPIO_A :
			GPIOA->ODR &=~ ( ( 0b11111111 )    << ( 8 ) );
			GPIOA->ODR |=(LOC_u8Value<<8);break;
		case GPIO_B :
			GPIOB->ODR&=~ ( ( 0b11111111 )    << ( 8 ) );
			GPIOB->ODR|=(LOC_u8Value<<8);break;
		case GPIO_C :
			GPIOC->ODR&=~ ( ( 0b11111111 )    << ( 8 ) );
			GPIOC->ODR|=(LOC_u8Value<<8);break;
		}
	}
	else if (LOC_u8Register==LOW_REG)
	{
		switch(LOC_u8Port)
		{
		case GPIO_A :
			GPIOA->ODR&=~ ( ( 0b11111111 ));
			GPIOA->ODR|=LOC_u8Value;break;
		case GPIO_B :
			GPIOB->ODR&=~ ( ( 0b11111111 ));
			GPIOB->ODR|=LOC_u8Value;break;
		case GPIO_C :
			GPIOC->ODR&=~ ( ( 0b11111111 ));
			GPIOC->ODR|=LOC_u8Value;break;
		}
	}


}

