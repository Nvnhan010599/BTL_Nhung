
#ifndef UART_DMA_H_
#define UART_DMA_H_

#include "stm32f4xx.h"
#include "system_timetick.h"
#include "stm32f4xx_it.h"
#include "stdio.h"
#include "stdlib.h"

void UART_Init(void);
void UART_Print( const char *pcString );
void UART_PrintNumber(const char *templateC,float a);

#endif /* UART_DMA_H_ */
