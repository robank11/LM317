#include "lcd.h"
#include "stdlib.h"
#include "draw_api.h"


uint8_t	oledBuffer[FRAME_BUFFER_SIZE];			    

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ALIENTEK��Ʒ��LCDҺ����
//������ռ�ýϴ�flash,�û����Ը����Լ���ʵ�����,ɾ��δ�õ���LCD��ʼ������.�Խ�ʡ�ռ�.
void LCD_Init(void)
{ 
	InitGraph();
}
  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(uint16_t color)
{
	ClearScreen();
}  



void oled_flush(void)
{
	
	//OLED_FILL(oledBuffer);
	uint8_t i,j;
	unsigned char *p;
	p=oledBuffer;

	for(i=0;i<8;i++)
	{
		WriteCmd(0xb0+i);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);	

		for(j=0;j<128;j++)
		{
				WriteDat(*p++);
		}
	}
}




















