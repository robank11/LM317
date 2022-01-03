/*
 * @Description: �˲�/kalman/��ͨ�˲�
 * @Author: zhangshenao
 * @Date: 2021-08-02 19:36:13
 * @LastEditTime: 2021-10-21 12:16:11
 * @LastEditors: zhangshenao
 * @Reference: 
 */
#include "Filter.h"

typedef struct
{
	float Eest_1; //�ϴι������
	float Eest_2; //���ι������
	float Emea;	  //�������
	float Xk_1;	  //�ϴι���ֵ
	float Xk_2;	  //��ǰ����ֵ
	float Kk;	  //������ϵ��
} Kalman_TypeDef;

/**
 * @description: kalman�˲�
 * @return {float} sample_value(�˲�ֵ)
 * @param {float} Zk(����ֵ)
 */
float Kalman_filter(float Zk)
{
	static Kalman_TypeDef Kalman_Struct;
	Kalman_Struct.Eest_1 = Kalman_Struct.Eest_2 = 10;
	Kalman_Struct.Emea = 0.001;														//�������
	float sample_value;																		//���
	Kalman_Struct.Kk = Kalman_Struct.Eest_1 / (Kalman_Struct.Eest_1 + Kalman_Struct.Emea);	//����kalmanϵ��
	Kalman_Struct.Xk_2 = Kalman_Struct.Xk_1 + Kalman_Struct.Kk * (Zk - Kalman_Struct.Xk_1); //��ǰ����ֵ����,����Kermanϵ��ȷ���ϴι���ֵ�͵�ǰ����ֵ��Ȩ��
	Kalman_Struct.Eest_2 = (1 - Kalman_Struct.Kk) * Kalman_Struct.Eest_1;					//�������
	Kalman_Struct.Xk_1 = Kalman_Struct.Xk_2;
	Kalman_Struct.Eest_1 = Kalman_Struct.Eest_2;
	sample_value = Kalman_Struct.Xk_2;
	return sample_value;
}

/**
 * @description: ��ͨ�˲�
 * @param {float} low_buf[](��ȥֵ������)
 * @return {float} sample_value(�˲�ֵ)
 */
float low_filter(float low_buf[])
{
	float sample_value;
	float X = 0.4;
	sample_value = (1 - X) * low_buf[1] + X * low_buf[0];
	return sample_value;
}
