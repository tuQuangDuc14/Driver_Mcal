#include <string.h>
#include "Header.h"
#include "Uart_TC_001.h"
#include "Uart_TS_001.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_Uart_IP.h"
#include "HuLa_Mcu_IP.h"

char msg[1024] = "Hello ThoNV12 \n\r";
USART_Handle_t usart2_handle;
void USART2_Init(void)
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle);
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

void Uart_TC_001(void)
{

	USART2_GPIOInit();
	USART2_Init();
	USART_PeripheralControl(USART2,ENABLE);
	 while(1)
	{
		USART_SendData(&usart2_handle,(uint8_t*)msg,16);
		break;
	}
	
	RESULT_Assert(1);
}

