#include "dac.h"

#include "math.h"
#include "usart.h"

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;
TIM_HandleTypeDef htim3;

#define DAC_BUFFER_SIZE			100
volatile uint16_t c_dac_buffer[DAC_BUFFER_SIZE];
volatile uint8_t g_dac_idx = 0;
void initDAC(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	gendataDAC();

	__HAL_RCC_DAC_CLK_ENABLE();
	DAC_ChannelConfTypeDef sConfig;
	hdac.Instance = DAC;
	HAL_DAC_Init(&hdac);

	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1);

	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);


	__HAL_RCC_TIM3_CLK_ENABLE();
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	// htim3.Init.Prescaler = 1 - 1;
	htim3.Init.Prescaler = 16800-1;			//  5KHz 
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	// htim3.Init.Period = 16800-1;		//1kHz
	htim3.Init.Period = 5000;		//1Hz
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_Base_Init(&htim3);
	HAL_TIM_Base_Start_IT(&htim3);


	HAL_NVIC_SetPriority(TIM3_IRQn,0,0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}

void gendataDAC(void)
{
	uint8_t k = 0;
	float s_value;
	float t = 0;
	for( k = 0; k < DAC_BUFFER_SIZE; ++k )
	{
		s_value = 0.5 + 0.2*sinf(2*3.14*10*t);
		t += 0.001;
		c_dac_buffer[k] = s_value * 4095;
	}

	// printUSART2("DAC DATA: \n");
	// for( k = 0; k < DAC_BUFFER_SIZE; ++k )
	// {
	// 	printUSART2(" %d ",c_dac_buffer[k]);
	// }
	// printUSART2("\n");
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3) //Fungsi Interrupt Timer
	{
		printUSART2("->DAC: Set value to [%d]\n",c_dac_buffer[g_dac_idx]);
		HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,c_dac_buffer[g_dac_idx++]);
		if(g_dac_idx >= DAC_BUFFER_SIZE)
		{
			g_dac_idx = 0;
		}

	}

}
