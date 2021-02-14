#ifndef __DAC_H
#define __DAC_H 

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

extern DAC_HandleTypeDef hdac;
extern DMA_HandleTypeDef hdma_dac1;
extern TIM_HandleTypeDef htim3;

void initDAC(void);
void gendataDAC(void);
#endif 
