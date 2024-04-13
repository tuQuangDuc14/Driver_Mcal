#include <string.h>
#include "Header.h"
#include "Mcl_TC_001.h"
#include "Mcl_TS_005.h"
#include "HuLa_Mcl_IP.h"
#include "HuLa_Mcl_IP.h"
#include "HuLa_Uart_IP.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_Mcu_IP.h"

MCL_Handle_t DMAUart;
USART_Handle_t USART2_Handle;

#define NVIC_IRQ_PRI15 15
#define DEST_ADDRESS (SRAM1_BASEADDR + 0x800)

char Tx_buf[16]="Hello thonv12 \r\n"; 
uint8_t a= 0, b=0;

void CallBack_ThoNV(MCL_Handle_t *pMCLHandle)
{
	
}

void USART2_Init(void)
{
	USART2_Handle.pUSARTx = USART2;
	USART2_Handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	USART2_Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	USART2_Handle.USART_Config.USART_Mode = USART_MODE_TXRX;
	USART2_Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	USART2_Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART2_Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&USART2_Handle);
}

void USART2_GPIOInit(void)
{
	GPIO_Handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode =7;

	//USART2 TX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_NO_2;
	GPIO_Init(&usart_gpios);

	//USART2 RX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&usart_gpios);
}

void Mcl_TC_001(void)
{
	MCL_PeriClockControl(DMA1, ENABLE);
	DMAUart.pDMAx = DMA1;
	DMAUart.pSTREAMx = DMA1_Stream6; 
	DMAUart.MCLConfig.Channel = DMA_CHANNEL_4 ;
	DMAUart.MCLConfig.Direction = DMA_MEMORY_TO_PERIPH;
	DMAUart.MCLConfig.FIFOMode = DMA_FIFOMODE_DISABLE;
	DMAUart.MCLConfig.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
	DMAUart.MCLConfig.MemAddrIncre = DMA_MINC_ENABLE;
	DMAUart.MCLConfig.MemBurst = DMA_MBURST_SINGLE;
	DMAUart.MCLConfig.MemDataWidth= DMA_MDATAALIGN_BYTE;
	DMAUart.MCLConfig.Mode = DMA_NORMAL;
	DMAUart.MCLConfig.PeriAddrIncre = DMA_PINC_DISABLE;
	DMAUart.MCLConfig.PeriBurst = DMA_PBURST_SINGLE;
	DMAUart.MCLConfig.PeriDataWidth = DMA_MDATAALIGN_BYTE;
	DMAUart.MCLConfig.Priority = DMA_PRIORITY_LOW;

	MCL_IRQPriorityConfig(IRQ_NO_DMA1_SREAM_6,NVIC_IRQ_PRI15);
	MCL_IRQInterruptConfig(IRQ_NO_DMA1_SREAM_6,ENABLE);

	if(MCL_Init(&DMAUart) == 0)
	{
		RESULT_Assert(0);
	}

	MCL_RegisterCallback(&DMAUart, DMA_CPLT_CB_ID, &CallBack_ThoNV);

	USART2_GPIOInit();
	USART2_Init();
	USART_IRQInterruptConfig(IRQ_NO_USART2,ENABLE);
	USART_PeripheralControl(USART2,ENABLE);

	MCL_Start_IT(&DMAUart,(uint32_t)Tx_buf,(uint32_t)&USART2_Handle.pUSARTx->DR,16);

	/* Send UART2_TX DMA Request to DMA1 Controler */
	USART2_Handle.pUSARTx->CR3 |=  ( 1 << USART_CR3_DMAT) ;

}

void DMA1_Stream6_IRQHandler(void)
{
	MCL_IRQHandling(&DMAUart);
}

void USART2_IRQHandler(void)
{
	USART_IRQHandling(&USART2_Handle);
}


void USART_ApplicationEventCallback( USART_Handle_t *pUSARTHandle,uint8_t ApEv)
{
   if(ApEv == USART_EVENT_RX_CMPLT)
   {
	   a =1;

   }else if (ApEv == USART_EVENT_TX_CMPLT)
   {
	   b =1;
   }
}
