#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"

volatile uint8_t g_pb_state;
volatile uint32_t g_interrupt_cnt;

int main(void)
{
	HAL_Init();

	initUSART2(921600);
	initSYSTIM();
	
///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// initialize 4 LED's on the board 
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 	
	// initalize push button on PA0
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	g_pb_state = 0;
	g_interrupt_cnt = 0;
	uint32_t cnt_time = getSYSTIM();
	while(1)
	{
		if(g_pb_state == 1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,0x01);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,0x01);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,0x01);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,0x01);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,0x00);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,0x00);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,0x00);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,0x00);
		}
		if(chk4TimeoutSYSTIM(cnt_time,100) == SYSTIM_TIMEOUT)
		{
			cnt_time = getSYSTIM();
			printUSART2("-> CNT [%d]\n",g_interrupt_cnt);

		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0)// PA0 or PB0 or PC0, all GPIO 0 are multiplexed
	{
		g_pb_state ^= 0x01;			// toggle PB state
		g_interrupt_cnt++;
	}
}
