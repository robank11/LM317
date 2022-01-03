/*
 * @Description: 
 * @Author: zhangshenao
 * @Date: 2021-10-12 20:17:11
 * @LastEditTime: 2021-10-22 19:58:49
 * @LastEditors: zhangshenao
 * @Reference: 
 */
#include "sys.h"


#define CPU_FREQUENCY_MHZ    168		// STM32时钟主频


/**
 * @description: 延迟us
 * @return {*}
 * @param {__IO uint32_t} delay
 */
void delay_us(__IO uint32_t delay)
{
    int last, curr, val;    
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}
/**
 * @description: GPIO快速初始化
 * @return {*}
 * @param {GPIO_TypeDef*} GPIOx
 * @param {uint32_t} BITx
 * @param {uint32_t} MODE
 * @param {uint32_t} OTYPE
 * @param {uint32_t} OSPEED
 * @param {uint32_t} PUPD
 */
void GPIO_Set(GPIO_TypeDef* GPIOx,uint32_t BITx,uint32_t MODE,uint32_t OTYPE,uint32_t OSPEED,uint32_t PUPD)
{  
	uint32_t pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=BITx&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->MODER|=MODE<<(pinpos*2);	//设置新的模式 
			if((MODE==0X01)||(MODE==0X02))	//如果是输出模式/复用功能模式
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//设置新的速度值  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				GPIOx->OTYPER|=OTYPE<<pinpos;		//设置新的输出模式
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//设置新的上下拉
		}
	}
} 
