#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

void delay_ms_soft(uint32_t ms);

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
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 	
	
	while(1)
	{
		delay_ms_soft(50);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,leds[n] & 0x01);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,(leds[n] >> 1) & 0x01);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,(leds[n] >> 2) & 0x01);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,(leds[n] >> 3) & 0x01);
		printUSART2("-> Hello world [%d]\n",n);
		n++;
		if(n == 8)
			n = 0;

	}
}


void delay_ms_soft(uint32_t ms)
{
	volatile uint32_t k = 65256 * ms;
	while(k--);
}
