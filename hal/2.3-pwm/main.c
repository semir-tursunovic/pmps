#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"


int main(void)
{
	HAL_Init();

	initUSART2(921600);
	initSYSTIM();
	initPWM();
	
	uint16_t pwm[19] = {0,2,5,11,23,50,109,235,509,999,509,235,109,50,23,11,5,2,0};
	uint8_t pwm_cnt = 0;
	while(1)
	{
		uint16_t duty_cycle = pwm[pwm_cnt++];
		if(pwm_cnt >= 19)
		{
			pwm_cnt = 0;
		}
		setPWM(duty_cycle,duty_cycle,duty_cycle,duty_cycle);
		delay_ms(1000);
	}
}


