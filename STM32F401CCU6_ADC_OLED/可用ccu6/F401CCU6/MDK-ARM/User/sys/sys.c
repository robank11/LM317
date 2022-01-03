/*
 * @Description: 
 * @Author: zhangshenao
 * @Date: 2021-10-12 20:17:11
 * @LastEditTime: 2021-10-22 19:58:49
 * @LastEditors: zhangshenao
 * @Reference: 
 */
#include "sys.h"


#define CPU_FREQUENCY_MHZ    168		// STM32ʱ����Ƶ


/**
 * @description: �ӳ�us
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
 * @description: GPIO���ٳ�ʼ��
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
		pos=1<<pinpos;	//һ����λ��� 
		curpin=BITx&pos;//��������Ƿ�Ҫ����
		if(curpin==pos)	//��Ҫ����
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->MODER|=MODE<<(pinpos*2);	//�����µ�ģʽ 
			if((MODE==0X01)||(MODE==0X02))	//��������ģʽ/���ù���ģʽ
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//���ԭ��������
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//�����µ��ٶ�ֵ  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//���ԭ��������
				GPIOx->OTYPER|=OTYPE<<pinpos;		//�����µ����ģʽ
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//�����µ�������
		}
	}
} 
