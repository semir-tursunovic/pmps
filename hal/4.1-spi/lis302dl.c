#include "lis302dl.h"

void initLIS302DL(void)
{
	uint8_t data,k ;
	uint32_t utmp32;
	
	initSPI1(SPI_BaudRatePrescaler_32);
	
	SPI1_CS_LOW;
	txByteSPI1((LIS302DL_CTRL_REG1));
	txByteSPI1(0x47);													// wakeup, select full scale +/-8g, enable x,y,z
	SPI1_CS_HIGH;
	
	delay_ms(100);														// delay of 3/fs = 30ms

	SPI1_CS_LOW;
	txByteSPI1(((LIS302DL_CTRL_REG1))|(LIS302DL_READ));
	utmp32 = rxByteSPI1();
	printUSART2("-> LIS302: LIS302DL_CTRL_REG1 [%x]\n",utmp32);
	SPI1_CS_HIGH;
	
	SPI1_CS_LOW;
	txByteSPI1(((LIS302DL_CTRL_REG1)+1)|(LIS302DL_READ));
	utmp32 = rxByteSPI1();
	printUSART2("-> LIS302: LIS302DL_CTRL_REG2 [%x]\n",utmp32);
	SPI1_CS_HIGH;
	
	SPI1_CS_LOW;
	txByteSPI1(((LIS302DL_CTRL_REG1)+2)|(LIS302DL_READ));
	utmp32 = rxByteSPI1();
	printUSART2("-> LIS302: LIS302DL_CTRL_REG3 [%x]\n",utmp32);
	SPI1_CS_HIGH;
	
	//delay_ms(2000);
	
	SPI1_CS_LOW;
	txByteSPI1((LIS302DL_REG_WHO_AM_I)|(LIS302DL_READ));
	
	utmp32 = rxByteSPI1();
	printUSART2("-> LIS302: LIS302DL_REG_WHO_AM_I [%x]\n",utmp32);
	
	SPI1_CS_HIGH;
}

void getDataLIS302DL(int8_t * accel_data)
{
	uint32_t utmp32;
	
	accel_data[0] = 0x00;
	accel_data[1] = 0x00;
	accel_data[2] = 0x00;
	
	SPI1_CS_LOW;
	txByteSPI1((LIS302DL_STATUS_REG)|(LIS302DL_READ));
	utmp32 = rxByteSPI1();
	SPI1_CS_HIGH;
	delay_us(100);
	
	uint8_t k, data[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
	SPI1_CS_LOW;
	txByteSPI1((LIS302DL_OUT_X)|(LIS302DL_READ));
	
	for(k=0;k<6;k++)
		data[k] = rxByteSPI1();
		
	SPI1_CS_HIGH;
	
	accel_data[0] = data[0];
	accel_data[1] = data[2];
	accel_data[2] = data[4];

	
	SPI1_CS_LOW;
	txByteSPI1((LIS302DL_CTRL_REG1));
	txByteSPI1(0x47);													// wakeup, select full scale +/-8g, enable x,y,z
	SPI1_CS_HIGH;
	
}
