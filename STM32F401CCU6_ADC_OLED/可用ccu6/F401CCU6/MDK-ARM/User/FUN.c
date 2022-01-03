#include "FUN.h"
#include "Filter.h"
#include "usbd_cdc_if.h"
#include "oled_draw.h"
#include "oled_font.h"
extern uint16_t ADC_CONV[2];
float P,uValue,iValue,OMG;
float low_buf_I[2],low_buf1_V[2];
uint8_t fpsMs,fpsms;


void ADC_Detect(void){
#if(USE_Filter==0)//���˲�
		iValue=3.3*ADC_CONV[1]/4096.0;										//����
		uValue=(6*3.3*ADC_CONV[0]/4096.0)-iValue/100.0;		//��ѹ
#elif(USE_Filter==1)//��ͨ�˲�
		low_buf_I[0]=3.3*ADC_CONV[1]/4096.0;										//����
		low_buf_I[1]=low_filter(low_buf_I);
		iValue=low_buf_I[1];
		low_buf1_V[0]=(6*3.3*ADC_CONV[0]/4096.0)-iValue/100.0;		//��ѹ
		low_buf1_V[1]=low_filter(low_buf1_V);
		uValue=low_buf1_V[1];
#elif(USE_Filter==2)//�������˲�
		iValue=Kalman_filter(3.3*ADC_CONV[1]/4096.0);										//����
		uValue=Kalman_filter((6*3.3*ADC_CONV[0]/4096.0)-iValue/100.0);		//��ѹ
#elif(USE_Filter==3)//˫�˲�

		low_buf1_V[0]=Kalman_filter((6*3.3*ADC_CONV[0]/4096.0)-iValue/100.0);		//��ѹ
		low_buf1_V[1]=low_filter(low_buf1_V);
		uValue=low_buf1_V[1];
#endif





		usb_printf("%f\r\n",uValue);					
}

uint8_t F_Overcurrent=0,F_Overvotage=0;
void Show_Power()
{ 
	DrawString(0,1,"U=     mV");//��ʾ��ѹ
	
	DrawNum(12,1,uValue*1000,5);
	DrawString(0,10,"PYX");//��ʾ��ѹ
	DrawString(0,20,"201202060116");//��ʾ��ѹ
//	DrawString(102,0,"fps");    //��ʾfps
//	DrawNum(88,0,(uint16_t)1000/fpsms,2);
	
//	else{DrawString(72,32,"          ");}

}
uint32_t now,lastDraw,now;
void Update(void){
  now=HAL_GetTick();
	if((uint16_t)(now - lastDraw) < fpsMs)
	{
		//pwrmgr_setState(PWR_ACTIVE_DISPLAY, PWR_STATE_IDLE);
		return;
	}
	fpsms = now - lastDraw;
	lastDraw = now;
	
	ADC_Detect();//ADC���
	Show_Power();//��ʾ������Ϣ
	
	
	
	UpdateScreen();
}


/************************IRQ_Server_FUN************************/
/**
  * @brief  Analog watchdog callback in non blocking mode 
  * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
	if(__HAL_ADC_GET_FLAG(hadc,ADC_FLAG_AWD)){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
		F_Overcurrent=1;
		
	}
}