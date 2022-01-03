#include "oled_config.h"
/* ��Ļ�����ļ����� */
#include "oled_driver.h"
#include "tim.h"

extern unsigned char  ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
extern unsigned char TempBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
unsigned int OledTimeMs=0;

//��ʼ��ͼ�ο⣬�뽫Ӳ����ʼ����Ϣ�������
void DriverInit(void)
{
	#if (TRANSFER_METHOD ==HW_IIC)
	I2C_Configuration();
	#elif (TRANSFER_METHOD ==HW_SPI)
	SPI_Configuration();
	#elif (TRANSFER_METHOD ==SW_SPI)
	SW_SPI_Configuration();
	#endif
	OLED_Init();
}

//Ϊ�ϲ��ṩӲ�������ӿ�OLED_FILL
void UpdateScreenBuffer(void)
{
	OLED_FILL(ScreenBuffer[0]);
}
//Ϊ�ϲ��ṩӲ�������ӿ�OLED_FILL
void UpdateTempBuffer(void)
{
	OLED_FILL(TempBuffer[0]);
}

//�뽫�˺�������1ms�ж��Ϊͼ���ṩʱ��
void OledTimeMsFunc(void)
{
	if (OledTimeMs != 0x00)
	{ 
	 OledTimeMs--;
	}
}
////д��һ���ֽ�
//static void WriteByteBuffer(u8 colnum,u8 row,u8 data)
//{
//	Screen_buffer[colnum][row]=data;
//}

////��һ���ֽ�
//static unsigned char ReadByteBuffer(unsigned char colnum,unsigned char row)
//{
//	return Screen_buffer[colnum][row];
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	 if (TIM_GET_ITSTATUS(&htim11, TIM_IT_UPDATE) != RESET)  //���TIM3�����жϷ������
  {
    TIM_GET_CLEAR_IT(&htim11, TIM_IT_UPDATE  );  //���TIMx�����жϱ�־
		OledTimeMsFunc();
  }
}

