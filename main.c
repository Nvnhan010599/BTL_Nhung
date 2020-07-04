
#include "PWM.h"
#include "Encoder.h"
#include "PID.h"
#include "UART.h"

float data =0.5;
int start = 0;
int on = 0;
float frequency = 20000;
int a =0;

uint16_t flag_10ms = 0;
uint16_t flag_100ms = 0;
int16_t v1 = 0,V;
int main(void)
{

	
 /* Initial Configuration */
	//UART_Init();

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
		ENC_config(TIM3,GPIOA,GPIO_Pin_6,GPIO_Pin_7); // Thay GPIOA-> GPIOB, GPIO_Pin_4,GPIO_Pin_5
		PWM_Pin();
		PWM_configOUT(20000); //20Khz
		PID_Init1(0.3,0.00,0);	
	/* Enable SysTick at 1ms interrupt */
		SysTick_Config(SystemCoreClock/1000);
	while(1)
		{
			//TIM_SetCompare1(TIM4,30);
			if(on)
			{
				PID_Calculate1(220);
			}
			else
			{
				Restart_PID1();
				TIM_SetCompare1(TIM4,0);
			}
			if(tick_flag == 1) //1ms
			{
				flag_10ms++;
				flag_100ms++;
				
				tick_flag = 0;
				
			}
			if(flag_10ms == 10)
			{
				
				v1 = ENCODER_Velocity(TIM3,1496);
				V = V_1Ts(v1);
				flag_10ms = 0;
			}
			if(flag_100ms == 100)
			{
				
				flag_100ms = 0;
			}

		}
}


