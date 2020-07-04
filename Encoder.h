/*
 * Encoder.h
 *
 *  Created on: Jun 21, 2020
 *      Author: Nhan
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

#include "main.h"

void ENC_config(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx,uint16_t A_GPIO_Pin_x,uint16_t B_GPIO_Pin_x );
int16_t ENCODER_Velocity(TIM_TypeDef* TIMx,uint16_t N);

#endif /* ENCODER_ENCODER_H_ */
