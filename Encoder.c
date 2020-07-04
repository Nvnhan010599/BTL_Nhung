/*
 * Encoder.c
 *
 *  Created on: Jun 21, 2020
 *      Author: Nhan
 */

#include "Encoder.h"

uint8_t Fs = 100;

void ENC_config(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx,uint16_t A_GPIO_Pin_x,uint16_t B_GPIO_Pin_x )
{
	GPIO_InitTypeDef enc;
	enc.GPIO_Pin = A_GPIO_Pin_x|B_GPIO_Pin_x;
	enc.GPIO_Mode = GPIO_Mode_AF;
	enc.GPIO_PuPd = GPIO_PuPd_UP;
	enc.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOx, &enc);

	GPIO_PinAFConfig(GPIOx, GPIO_PinSource4, GPIO_AF_TIM3);  //GPIO_PinSource4
	GPIO_PinAFConfig(GPIOx, GPIO_PinSource4, GPIO_AF_TIM3);  //GPIO_PinSource5

	TIM_TimeBaseInitTypeDef tim_enc;
	tim_enc.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_enc.TIM_CounterMode = TIM_CounterMode_Up;
	tim_enc.TIM_Prescaler = 0;
	tim_enc.TIM_Period = 65535;

	TIM_TimeBaseInit(TIMx, &tim_enc);

	TIM_SetCounter(TIMx, 0);

	TIM_EncoderInterfaceConfig(TIMx, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	TIM_Cmd(TIMx, ENABLE);

}

int16_t ENCODER_Velocity(TIM_TypeDef* TIMx,uint16_t N)
{

	int16_t xungENC ;
	xungENC = TIM_GetCounter(TIMx);
	xungENC *=Fs*60/N;
	TIM_SetCounter(TIMx,0);
	return xungENC;

}
