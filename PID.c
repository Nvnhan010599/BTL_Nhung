/*
 * PID.c
 *
 *  Created on: Jun 21, 2020
 *      Author: Nhan
 */
#include "PID.h"

PID_Para motor1;
float V_1 = 0,tempV1 = 0;
float uk1 ;
float to1 = 0.01,Ts = 0.01;
float v_preFilter1R = 0, v_Filter1R,tempR = 0;

float V_1Ts(float V) // ham lay mau
{
	
	V_1 = (1 - exp(-1/to1*Ts))*v_preFilter1R + exp(-1/to1*Ts)*v_Filter1R ;
	tempR = v_Filter1R;
	v_Filter1R = V_1;
	v_preFilter1R = V;
	return V_1;
}

void PID_Init1(float Kp, float Ki, float Kd) // ham khoi tao
{
	motor1.Kp = Kp;
	motor1.Ki = Ki;
	motor1.Kd = Kd;
	motor1.Ts_ = 0.01;
	motor1.ek = 0 ;
	motor1.ek_1 = 0 ;
	motor1.ek_2 = 0;
	motor1.uk = 0;
	motor1.uk_1 = 0 ;
}

void Restart_PID1(void)
{
	motor1.ek = 0 ;
	motor1.ek_1 = 0 ;
	motor1.ek_2 = 0;
	motor1.uk = 0;
	motor1.uk_1 = 0 ;
	V_1 = 0;
}

void PID_Calculate1(float Vd_1) // Vd_1 RPM
{

	motor1.ek =  Vd_1 - V_1;
	motor1.uk = motor1.uk_1 + motor1.Kp*(motor1.ek-motor1.ek_1)
													+ motor1.Ki*motor1.Ts_*(motor1.ek + motor1.ek_1)/2
													+ motor1.Kd*(motor1.ek-2*motor1.ek_1+motor1.ek_2)/motor1.Ts_;

	motor1.uk_1 = motor1.uk;
	motor1.ek_2 = motor1.ek_1;
	motor1.ek_1 = motor1.ek;
	int period = 0;
	get_period(&period);
	uk1 = fabs((float)motor1.uk*period/100);
	if(uk1 > 90) uk1 = 90; // Saturation
	
	if(Vd_1 >= 0)
	{
		GPIOD->BSRRH |= 1<<13; // OFF
	}
	else
	{
		GPIOD->BSRRL |= 1<<13;  // ON
	}
	
		TIM_SetCompare1(TIM4,uk1);
	
}
