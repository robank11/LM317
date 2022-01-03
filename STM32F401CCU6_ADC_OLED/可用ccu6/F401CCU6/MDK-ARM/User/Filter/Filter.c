/*
 * @Description: 滤波/kalman/低通滤波
 * @Author: zhangshenao
 * @Date: 2021-08-02 19:36:13
 * @LastEditTime: 2021-10-21 12:16:11
 * @LastEditors: zhangshenao
 * @Reference: 
 */
#include "Filter.h"

typedef struct
{
	float Eest_1; //上次估计误差
	float Eest_2; //本次估计误差
	float Emea;	  //测量误差
	float Xk_1;	  //上次估计值
	float Xk_2;	  //当前估计值
	float Kk;	  //卡尔曼系数
} Kalman_TypeDef;

/**
 * @description: kalman滤波
 * @return {float} sample_value(滤波值)
 * @param {float} Zk(输入值)
 */
float Kalman_filter(float Zk)
{
	static Kalman_TypeDef Kalman_Struct;
	Kalman_Struct.Eest_1 = Kalman_Struct.Eest_2 = 10;
	Kalman_Struct.Emea = 0.001;														//测量误差
	float sample_value;																		//结果
	Kalman_Struct.Kk = Kalman_Struct.Eest_1 / (Kalman_Struct.Eest_1 + Kalman_Struct.Emea);	//计算kalman系数
	Kalman_Struct.Xk_2 = Kalman_Struct.Xk_1 + Kalman_Struct.Kk * (Zk - Kalman_Struct.Xk_1); //当前估计值计算,根据Kerman系数确定上次估计值和当前测量值的权重
	Kalman_Struct.Eest_2 = (1 - Kalman_Struct.Kk) * Kalman_Struct.Eest_1;					//更新误差
	Kalman_Struct.Xk_1 = Kalman_Struct.Xk_2;
	Kalman_Struct.Eest_1 = Kalman_Struct.Eest_2;
	sample_value = Kalman_Struct.Xk_2;
	return sample_value;
}

/**
 * @description: 低通滤波
 * @param {float} low_buf[](过去值缓冲区)
 * @return {float} sample_value(滤波值)
 */
float low_filter(float low_buf[])
{
	float sample_value;
	float X = 0.4;
	sample_value = (1 - X) * low_buf[1] + X * low_buf[0];
	return sample_value;
}
