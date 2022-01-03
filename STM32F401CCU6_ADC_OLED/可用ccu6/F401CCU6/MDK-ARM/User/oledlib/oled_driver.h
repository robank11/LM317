#ifndef __OLED_DRIVER_H
#define	__OLED_DRIVER_H
#include "main.h"
#include "oled_config.h"
#include "oled_basic.h"


#if (TRANSFER_METHOD ==HW_IIC)

	#if (USE_HW_IIC ==IIC_1)
		#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78
		/*STM32F103C8T6芯片的硬件I2C: PB6 -- SCL; PB7 -- SDA */
		#define IIC_RCC_APB1Periph_I2CX   	RCC_APB1Periph_I2C1
		#define IIC_RCC_APB2Periph_GPIOX  	RCC_APB2Periph_GPIOB
		#define IIC_GPIOX                		GPIOB
		#define IIC_SCL_Pin_X								GPIO_Pin_6
		#define IIC_SDA_Pin_X        				GPIO_Pin_7
		#define I2CX                  			I2C1
	#elif (USE_HW_IIC ==IIC_2)
		#define IIC_RCC_APB1Periph_I2CX   	RCC_APB1Periph_I2C2
		#define IIC_RCC_APB2Periph_GPIOX  	RCC_APB2Periph_GPIOB
		#define IIC_GPIOX                		GPIOB
		#define IIC_SCL_Pin_X								GPIO_Pin_10
		#define IIC_SDA_Pin_X       			 	GPIO_Pin_11
		#define I2CX                  			I2C2
	#endif
	
#elif (TRANSFER_METHOD ==SW_IIC)



#elif (TRANSFER_METHOD ==HW_SPI)
	
	#if (USE_HW_SPI==SPI_1)
		
		
		
	#elif (USE_HW_SPI==SPI_2)
		#define SPIX                      SPI2

		//CS片选（软件片选）
		#define SPI_CS_Pin_X              GPIO_PIN_10
		#define SPI_CS_GPIOX							GPIOA
		//复位引脚
		#define SPI_RES_PIN 							GPIO_PIN_8
		#define SPI_RES_GPIOX							GPIOA
		//控制引脚
		#define SPI_DC_PIN 								GPIO_PIN_9
		#define SPI_DC_GPIOX							GPIOA
	#endif

#elif (TRANSFER_METHOD ==SW_SPI)


#endif

void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void SPI_Configuration(void);

void SW_SPI_Configuration(void);

void SPI_WriterByte(unsigned char dat);
void WriteCmd(unsigned char cmd);
void WriteDat(unsigned char Dat);
void OLED_Init(void);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_FILL(unsigned char BMP[]);

#endif //__OLED_DRIVER_H
