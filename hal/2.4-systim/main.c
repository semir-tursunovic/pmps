#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"


int main(void)
{
	HAL_Init();

	uint16_t leds[8] = {0xF,0xE,0xC,0x8,0x0,0x1,0x3,0x7};
	uint8_t n = 0;
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// initialize 4 LED's on the board 
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	initUSART2(921600);
	initSYSTIM();
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 	
	
	uint32_t led1_timer = getSYSTIM();		// 100ms
	uint32_t led2_timer = getSYSTIM();
	uint32_t led3_timer = getSYSTIM();
	uint32_t led4_timer = getSYSTIM();
	while(1)
	{
		if(chk4TimeoutSYSTIM(led1_timer,100) == SYSTIM_TIMEOUT)
		{
			led1_timer = getSYSTIM();
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
		}
		if(chk4TimeoutSYSTIM(led2_timer,250) == SYSTIM_TIMEOUT)
		{
			led2_timer = getSYSTIM();
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
		}
		if(chk4TimeoutSYSTIM(led3_timer,500) == SYSTIM_TIMEOUT)
		{
			led3_timer = getSYSTIM();
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
		}
		if(chk4TimeoutSYSTIM(led4_timer,1000) == SYSTIM_TIMEOUT)
		{
			led4_timer = getSYSTIM();
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_15);
		}
	}
}


