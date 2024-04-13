#include <string.h>
#include "Header.h"
#include "Uart_TC_002.h"
#include "Uart_TS_001.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_Uart_IP.h"
#include "HuLa_Mcu_IP.h"

char msg1[10];

USART_Handle_t usart2_handle1;

void USART2_Init1(void)
{
	usart2_handle1.pUSARTx = USART2;
	usart2_handle1.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart2_handle1.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle1.USART_Config.USART_Mode = USART_MODE_ONLY_RX;
	usart2_handle1.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle1.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle1.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle1);
}

void USART2_GPIOInit1(void)
{
	GPIO_Handle_t usart_gpios1;

	usart_gpios1.pGPIOx = GPIOA;
	usart_gpios1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios1.GPIO_PinConfig.GPIO_PinAltFunMode =7;

	//USART2 TX
	usart_gpios1.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_NO_2;
	GPIO_Init(&usart_gpios1);

	//USART2 RX
	usart_gpios1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&usart_gpios1);
}

void Uart_TC_002(void)
{

	USART2_GPIOInit1();
	USART2_Init1();
	USART_PeripheralControl(USART2,ENABLE);

	 while(1)
	{
		break; /* chạy thật thì bỏ đi*/
	    USART_ReceiveData( &usart2_handle1,(uint8_t *)msg1, 6 );
	}
	
	RESULT_Assert(1);
}

