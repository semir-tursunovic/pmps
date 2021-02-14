#ifndef __LIS302DL_H_
#define __LIS302DL_H_

#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "spi.h"

#define LIS302DL_REG_WHO_AM_I					0x0F
#define LIS302DL_REG_WHO_AM_I_VAL				0x3F

#define LIS302DL_READ							0x80
#define LIS302DL_MULTIPLE						0x40

#define LIS302DL_CTRL_REG1						0x20
#define LIS302DL_CTRL_REG2						0x21
#define LIS302DL_STATUS_REG						0x27
#define LIS302DL_OUT_X 							0x29
#define LIS302DL_OUT_Y 							0x2B
#define LIS302DL_OUT_Z 							0x2D

void 		initLIS320DL(void);
void 		getDataLIS302DL(int8_t * accel_data);

#endif 
