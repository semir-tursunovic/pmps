#include "spi.h"

SPI_HandleTypeDef hspi1;

void initSPI1(uint16_t prescaler)
{/// init SPI1 in master mode
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// SPI1 Pin configuration
	///-----------------------------------------------------------------
	/// PE3 = CS
	/// PA5 = SCK
	/// PA6 = MISO
	/// PA7 = MOSI
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//

	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	


	__HAL_RCC_SPI1_CLK_ENABLE();
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	HAL_SPI_Init(&hspi1);

	// hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	// hspi1.Init.CRCPolynomial = 10;
	
	// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 								//
	// GPIOA->MODER |= 0x0000A800; 										// 
	// GPIOA->AFR[0] |= 0x55500000;										//   
	// GPIOA->OSPEEDR |= 0x0000A800;										// 
	
	// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	// GPIOE->MODER |= 0x00000040; 
	// GPIOE->OTYPER &= ~(0x00000008);
	// GPIOE->OSPEEDR |= 0x00000080;										// 
	// SPI1_CS_HIGH;
	
	// RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 								// 	
	// SPI1->CR1 = (SPI_CR1_MSTR);											// enable 8 bit data & master mode			
	// SPI1->CR1 |= (SPI_CR1_SSI)|(SPI_CR1_SSM);
	
	// SPI1->CR1 |= prescaler;		
	// SPI1->CR1 |= (SPI_CR1_SPE);											// 
}

uint8_t rxByteSPI1(void)
{///  receive data using SPI1
	uint8_t data;
	
	HAL_SPI_Receive(&hspi1, &data,1,10000);
	// SPI1->DR = 0x00;						 							// 
	// while(!(SPI1->SR & SPI_I2S_FLAG_TXE)); 								// 
	// while(!(SPI1->SR & SPI_I2S_FLAG_RXNE)); 							// 
	// while(SPI1->SR & SPI_I2S_FLAG_BSY); 								//	
	// data = SPI1->DR; 													//
	
	return data;
}	

uint8_t txByteSPI1(uint8_t data)
{/// send data using SPI1
	// uint8_t tmp;

	HAL_SPI_Transmit(&hspi1, &data,1,10000);
	// SPI1->DR = data; 													//
	// while(!(SPI1->SR & SPI_I2S_FLAG_TXE));								// 
	// while(!(SPI1->SR & SPI_I2S_FLAG_RXNE)); 							// 
	// while(SPI1->SR & SPI_I2S_FLAG_BSY); 								// 
	// tmp = SPI1->DR; 													// 
		
	return 0;
	// return tmp;
}

