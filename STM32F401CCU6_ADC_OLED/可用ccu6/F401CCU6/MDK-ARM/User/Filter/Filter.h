/*
 * @Description: ÂË²¨/kalman/µÍÍ¨ÂË²¨
 * @Author: zhangshenao
 * @Date: 2021-08-02 19:36:13
 * @LastEditTime: 2021-10-21 12:17:54
 * @LastEditors: zhangshenao
 * @Reference: 
 */
#ifndef __FILTER_H__
#define __FILTER_H__
#include "stm32f4xx.h" // Device header

float low_filter(float low_buf[]);

float Kalman_filter(float Zk);

#endif
