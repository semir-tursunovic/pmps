#include "stm32f4xx.h"

void delay_soft_ms(uint32_t cnt);

int main(void)
{
	uint8_t tmp = 0;
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// inicijalizacija
	///-----------------------------------------------------------------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  								//
    GPIOD->MODER |= 0x55000000;             							//
    GPIOD->OTYPER |= 0x00000000;										//
    GPIOD->OSPEEDR |= 0xFF000000; 										//
	
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~0x00000003;  										//
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 	
	
	
	while(1)
	{
		if((GPIOA->IDR & 0x0001) == 0x0001)
		{
			if(tmp == 0) 
				tmp = 1;
			else
				tmp = 0;
			
			delay_soft_ms(1000);	
		}		
		
		if(tmp == 1)
		{
			GPIOD->ODR |= 0xF000;
		}
		else
		{
			GPIOD->ODR &= ~0xF000;
		}
	}
}


void delay_soft_ms(uint32_t cnt)
{/// primitivna rutina za kasnjenje 									
	volatile uint32_t time = cnt*10500;											
																		// izbjegavati softverski definirane rutine																// za kasnjenje
	while(time)
	{
		time--;
	}														
	
	return;
}
