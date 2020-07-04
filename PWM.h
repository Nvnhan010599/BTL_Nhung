/*
 * PWM.h
 *
 *  Created on: Jun 10, 2020
 *      Author: Nhan
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_
#include "main.h"
void PWM_configOUT(float freq);
void PWM_Pin(void);
void get_period(int *per);
#endif /* PWM_PWM_H_ */
