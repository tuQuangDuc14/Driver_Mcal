

#ifndef HULA_UART_IP_H_
#define HULA_UART_IP_H_

#include "Header.h"

/*structure for USARTx peripheral*/
typedef struct
{
	uint8_t USART_Mode;            /*tx only, rx only, txrx*/
	uint32_t USART_Baud;           /*baudrate*/
	uint8_t USART_NoOfStopBits;    /*stop bit*/
	uint8_t USART_WordLength;      /*8bit hay 9bit*/
	uint8_t USART_ParityControl;   /*chan hay le*/
	uint8_t USART_HWFlowControl;
}USART_Config_t;

typedef struct
{
	USART_RegDef_t *pUSARTx;         /*instance*/
	USART_Config_t   USART_Config;  
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxBusyState;
	uint8_t RxBusyState;
}USART_Handle_t;

/* Possible options for USART_Mode*/
#define USART_MODE_ONLY_TX 	0
#define USART_MODE_ONLY_RX 	1
#define USART_MODE_TXRX  	2

/*baudrate*/
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000

/*USART_ParityControl*/
#define USART_PARITY_EN_ODD   2
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_DISABLE  0

/* WordLength*/
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1

/* NoOfStopBits*/
#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2
#define USART_STOPBITS_1_5   3

/*HWFlowControl*/
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

/*USART flags*/
#define USART_FLAG_TXE 			( 1 << USART_SR_TXE)   /*trasmit enable*/
#define USART_FLAG_RXNE 		( 1 << USART_SR_RXNE)  /*recieve enable*/
#define USART_FLAG_TC 			( 1 << USART_SR_TC)    /*transmit complete*/

/*Application states*/
#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0

#define 	USART_EVENT_TX_CMPLT   0
#define		USART_EVENT_RX_CMPLT   1
#define		USART_EVENT_IDLE       2
#define		USART_EVENT_CTS        3
#define		USART_EVENT_PE         4
#define		USART_ERR_FE     	   5
#define		USART_ERR_NE    	   6
#define		USART_ERR_ORE    	   7

/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void  USART_ReceiveData(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len);
#endif /* HULA_UART_IP_H_ */



