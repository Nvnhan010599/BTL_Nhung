/*
 * PID.h
 *
 *  Created on: Jun 21, 2020
 *      Author: Nhan
 */

#ifndef PID_PID_H_
#define PID_PID_H_

#include "main.h"

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float ek;
	float ek_1;
	float ek_2;
	float uk;
	float uk_1;
	float Ts_;

}PID_Para;

float V_1Ts(float V); // ham lay mau
void PID_Init1(float Kp, float Ki, float Kd); // ham khoi tao
void Restart_PID1(void);
void PID_Calculate1(float Vd_1); // Vd_1 RPM



#endif /* PID_PID_H_ */
