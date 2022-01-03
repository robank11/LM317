/*
 * @Description: 
 * @Author: zhangshenao
 * @Date: 2021-10-12 20:17:11
 * @LastEditTime: 2021-10-25 15:39:04
 * @LastEditors: zhangshenao
 * @Reference: 
 */
#ifndef __SYS_H
#define __SYS_H	
#include "stm32f4xx_hal.h"


//0,不支持ucos
//1,支持ucos
#define SYSTEM_SUPPORT_UCOS		0		//定义系统文件夹是否支持UCOS

void delay_us(__IO uint32_t delay);
void GPIO_Set(GPIO_TypeDef* GPIOx,uint32_t BITx,uint32_t MODE,uint32_t OTYPE,uint32_t OSPEED,uint32_t PUPD);
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

/* 定义控制IO的宏 */
#define GPIO_OX1		 digitalToggle(GPIOG,GPIO_Pin_13)
#define GPIO_OX2		 digitalToggle(GPIOG,GPIO_Pin_14)
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40024014 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40028014 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40022014    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814    

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40010810 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40010C10 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40011010
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40011410 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40011810
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40011A10
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40011E10
 

//Ex_NVIC_Config专用定义
#define GPIO_A 				0
#define GPIO_B 				1
#define GPIO_C				2
#define GPIO_D 				3
#define GPIO_E 				4
#define GPIO_F 				5
#define GPIO_G 				6 
#define GPIO_H 				7 
#define GPIO_I 				8 

#define FTIR   				1  		//下降沿触发
#define RTIR   				2  		//上升沿触发

//GPIO设置专用宏定义
#define GPIO_MODE_IN    	0		//普通输入模式
#define GPIO_MODE_OUT		1		//普通输出模式
#define GPIO_MODE_AF		2		//AF功能模式
#define GPIO_MODE_AIN		3		//模拟输入模式

#define GPIO_SPEED_2M		0		//GPIO速度2Mhz
#define GPIO_SPEED_25M		1		//GPIO速度25Mhz
#define GPIO_SPEED_50M		2		//GPIO速度50Mhz
#define GPIO_SPEED_100M		3		//GPIO速度100Mhz

#define GPIO_PUPD_NONE		0		//不带上下拉
#define GPIO_PUPD_PU		1		//上拉
#define GPIO_PUPD_PD		2		//下拉
#define GPIO_PUPD_RES		3		//保留 

#define GPIO_OTYPE_PP		0		//推挽输出
#define GPIO_OTYPE_OD		1		//开漏输出 

//GPIO引脚编号定义
#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15 

 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入




#endif
