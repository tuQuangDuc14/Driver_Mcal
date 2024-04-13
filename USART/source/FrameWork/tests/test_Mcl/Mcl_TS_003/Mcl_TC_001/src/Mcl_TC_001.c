#include <string.h>
#include "Header.h"
#include "Mcl_TC_001.h"
#include "Mcl_TS_003.h"
#include "HuLa_Mcl_IP.h"
#include "HuLa_Mcl_IP.h"
#include "HuLa_Gpio_IP.h"

GPIO_Handle_t GpioLed;
MCL_Handle_t DMALed;
#define NVIC_IRQ_PRI15 15

uint8_t Data_src = 0x01, Data_des= 0;
volatile uint8_t Check = 0;

void delay(void)
{
	uint32_t i = 0;
	for ( i = 0; i < 500000 / 2; i++);
}

void Gpio_PinInit()
{
	/* This is led gpio configuration */
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed);
}

void CallBack_ThoNV(MCL_Handle_t *pMCLHandle)
{
	Check = 1;
}

/* Mem to mem varible */
void Mcl_TC_001(void)
{
	Gpio_PinInit();

	MCL_PeriClockControl(DMA2, ENABLE);

	DMALed.pDMAx = DMA2;
	DMALed.pSTREAMx = DMA2_Stream0; /* Chọn đại vì M2M không cần */
	DMALed.MCLConfig.Channel = DMA_CHANNEL_0 ;
	DMALed.MCLConfig.Direction = DMA_MEMORY_TO_MEMORY;
	DMALed.MCLConfig.FIFOMode = DMA_FIFOMODE_ENABLE;
	DMALed.MCLConfig.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
	DMALed.MCLConfig.MemAddrIncre = DMA_MINC_DISABLE;
	DMALed.MCLConfig.MemBurst = DMA_MBURST_SINGLE;
	DMALed.MCLConfig.MemDataWidth= DMA_MDATAALIGN_BYTE;
	DMALed.MCLConfig.Mode = DMA_NORMAL;
	DMALed.MCLConfig.PeriAddrIncre = DMA_PINC_DISABLE;
	DMALed.MCLConfig.PeriBurst = DMA_PBURST_SINGLE;
	DMALed.MCLConfig.PeriDataWidth = DMA_MDATAALIGN_BYTE;
	DMALed.MCLConfig.Priority = DMA_PRIORITY_LOW;

	MCL_IRQPriorityConfig(IRQ_NO_DMA2_SREAM_0,NVIC_IRQ_PRI15);
	MCL_IRQInterruptConfig(IRQ_NO_DMA2_SREAM_0,ENABLE);


	if(MCL_Init(&DMALed) == 0)
	{
		RESULT_Assert(0);
	}

	MCL_RegisterCallback(&DMALed, DMA_CPLT_CB_ID, &CallBack_ThoNV);

	MCL_Start_IT(&DMALed,(uint32_t)&Data_src,(uint32_t)&Data_des,1);

	RESULT_Assert(Data_des == 0x01);
	RESULT_Assert(Check == 0x01);
}

void DMA2_Stream0_IRQHandler(void)
{
	MCL_IRQHandling(&DMALed);
}

