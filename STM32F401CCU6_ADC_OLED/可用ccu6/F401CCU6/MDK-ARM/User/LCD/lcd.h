#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h" 

#define FRAME_WIDTH			128
#define FRAME_HEIGHT		64
#define FRAME_BUFFER_SIZE	((FRAME_WIDTH * FRAME_HEIGHT) / 8)
void LCD_Init(void);													   	//初始化													//关显示
void LCD_Clear(uint16_t Color);	 												//清屏
void oled_flush(void);






#endif  
	 
	 



