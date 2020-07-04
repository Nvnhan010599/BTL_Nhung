
/* Includes ------------------------------------------------------------------*/
#include "system_timetick.h"

uint32_t	tick_count;
uint32_t	tick_flag;


void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}
	  
void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  tick_count++;
	tick_flag = 1;
}
__IO uint16_t IC2Value = 0;
__IO uint16_t DutyCycle = 0;
__IO uint32_t Frequency = 0;
uint32_t tmp = 0;
void TIM5_IRQHandler(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	  RCC_GetClocksFreq(&RCC_Clocks);

	  /* Clear TIM5 Capture compare interrupt pending bit */
	  TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);

	  /* Get the Input Capture value */
	  IC2Value = TIM_GetCapture2(TIM5);

	  if (IC2Value != 0)
	  {
	    /* Duty cycle computation */
	    DutyCycle = (TIM_GetCapture1(TIM5) * 100) / IC2Value;

	    /* Frequency computation
	       TIM5 counter clock = (RCC_Clocks.HCLK_Frequency)/2 */
	    tmp = RCC_Clocks.SYSCLK_Frequency;
	    Frequency = (RCC_Clocks.HCLK_Frequency/2) / IC2Value;
	    //Frequency = 84000000 / IC2Value;
	  }
	  else
	  {
	    DutyCycle = 0;
	    Frequency = 0;
		}
 }


