#include "UART.h"

#define	  Tx_BUFF_SIZE		16
#define   Rx_BUFF_SIZE      8
void init_main(void);
void UART_Print( const char *pcString );
void UART_PrintNumber(const char *templateC,float a);


uint8_t 	rxbuff[Rx_BUFF_SIZE];
char txbuff[Tx_BUFF_SIZE];	

float kp,ki,kd;
char Rx_Data[Rx_BUFF_SIZE];



void UART_Init(void)
{
	/* Create the typedef for GPIO,USART,DMA,NVIC */
  GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;  
	DMA_InitTypeDef   DMA_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;	
   
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	/* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Connect UART4 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); 

  /* GPIO Configuration for UART4 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIO Configuration for USART Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(UART4, &USART_InitStructure);

  /* Enable USART */
  USART_Cmd(UART4, ENABLE);
	/* Enable UART4 DMA */
  USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
	/* Enable UART4 DMA */
  USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); 
	
	/* DMA1 Stream2 Channel4 for USART4 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = Rx_BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream2, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream2, ENABLE);
	
	/* DMA1 Stream4 Channel4 for USART4 Tx configuration */			
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = Tx_BUFF_SIZE;
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream4, ENABLE);
	
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);
}

void DMA1_Stream2_IRQHandler(void)
{
  /* Clear the DMA1_Stream2 TCIF2 pending bit */
  DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);

  for(uint16_t i=0; i<Rx_BUFF_SIZE; i++)
    Rx_Data[i] = rxbuff[i];	
	DMA_Cmd(DMA1_Stream2, ENABLE);
	if (Rx_Data[0] == 'K')
		{
			if(Rx_Data[1] ==  'p')
				{
				kp = atof(&Rx_Data[2]);
				}
			if(Rx_Data[1] ==  'i')
				{
				ki = atof(&Rx_Data[2]);
				}
			if(Rx_Data[1] ==  'd')
				{
				kd = atof(&Rx_Data[2]);
				}
		}
}
// Send simple data to UART
void UART_Print( const char *pcString ) 
{
 while(*pcString != '\0')
	{
		USART_SendData(UART4, *pcString);
		while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
		pcString++;
	}
 }
int check = -1;
 // Send multiple data to UART
void UART_PrintNumber(const char *templateC,float a)
{
	 check = snprintf(txbuff,8,templateC,a);
	 UART_Print(&txbuff[0]);
	 UART_Print("\r\n");
}
