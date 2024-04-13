#include <string.h>
#include "Header.h"
#include "Mcl_TC_001.h"
#include "Mcl_TS_001.h"
#include "HuLa_Mcl_IP.h"
#include "HuLa_Mcl_IP.h"
#include "HuLa_Gpio_IP.h"

GPIO_Handle_t GpioLed;
MCL_Handle_t DMALed;

uint32_t Data_Src_Led = 0xFFFF;
uint32_t Data_src = 0x01, Data_des= 0;

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

/* Mem to mem */
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
	DMALed.MCLConfig.MemDataWidth= DMA_MDATAALIGN_WORD;
	DMALed.MCLConfig.Mode = DMA_NORMAL;
	DMALed.MCLConfig.PeriAddrIncre = DMA_PINC_DISABLE;
	DMALed.MCLConfig.PeriBurst = DMA_PBURST_SINGLE;
	DMALed.MCLConfig.PeriDataWidth = DMA_MDATAALIGN_WORD;
	DMALed.MCLConfig.Priority = DMA_PRIORITY_LOW;

	if(MCL_Init(&DMALed) == 0)
	{
		RESULT_Assert(0);
	}

	MCL_Start(&DMALed,(uint32_t)&Data_Src_Led,(uint32_t)&GPIOD->ODR,4);
	MCL_WaitForTransfer(&DMALed);

	RESULT_Assert(GPIO_ReadFromInputPin(GPIOD,GPIO_PIN_NO_13) == 1 );
}

