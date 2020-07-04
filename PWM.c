/*
 * PWM.c
 *
 *  Created on: Jun 10, 2020
 *      Author: Nhan
 */
#include "PWM.h"

void PWM_Pin(void)
{
	GPIO_InitTypeDef pwm_out; //PD12
	pwm_out.GPIO_Pin = GPIO_Pin_12; //
	pwm_out.GPIO_Mode = GPIO_Mode_AF;
	pwm_out.GPIO_OType =GPIO_OType_PP;
	pwm_out.GPIO_PuPd = GPIO_PuPd_UP;
	pwm_out.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &pwm_out);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); // xuat PWM
	
	GPIO_InitTypeDef dir;
	dir.GPIO_Pin = GPIO_Pin_13;
	dir.GPIO_Mode = GPIO_Mode_OUT;
	dir.GPIO_OType = GPIO_OType_PP;
	dir.GPIO_PuPd = GPIO_PuPd_DOWN;
	dir.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&dir);
	

}
uint32_t period = 0 ;
uint32_t prescale = 0;

void PWM_configOUT(float freq)
{	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
//RCC_Clocks.HCLK_Frequency
	prescale = RCC_Clocks.HCLK_Frequency/2/2000000 - 1;
	period = RCC_Clocks.HCLK_Frequency/2/((prescale + 1)*freq) - 1 ;
//RCC_Clocks.HCLK_Frequency/2/((prescale + 1)*1000) - 1 ;

	TIM_TimeBaseInitTypeDef Timer_PWM;
	Timer_PWM.TIM_ClockDivision = 0;
	Timer_PWM.TIM_CounterMode = TIM_CounterMode_Up; 
	Timer_PWM.TIM_Prescaler = prescale;
	Timer_PWM.TIM_Period = period;
	TIM_TimeBaseInit(TIM4, &Timer_PWM);

	TIM_OCInitTypeDef PWM;
	PWM.TIM_OCMode = TIM_OCMode_PWM1;
	PWM.TIM_OCPolarity = TIM_OCPolarity_High;
	PWM.TIM_OutputState = TIM_OutputState_Enable;
	PWM.TIM_Pulse = 0;
	TIM_OC1Init(TIM4, &PWM);  //CH1
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

void get_period(int *per)
{
	*per = period;
}





