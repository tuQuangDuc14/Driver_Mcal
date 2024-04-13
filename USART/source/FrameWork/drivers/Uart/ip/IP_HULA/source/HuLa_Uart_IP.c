#include "HuLa_Uart_IP.h"


/*enable clock for uart*/
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pUSARTx == USART1)
		{
			USART1_PCCK_EN();
		} else if(pUSARTx == USART2)
		{
			USART2_PCCK_EN();
		} else if(pUSARTx == USART3)
		{
			USART3_PCCK_EN();
		}else if(pUSARTx == UART4)
		{
			UART4_PCCK_EN();
		}else if(pUSARTx == UART5)
		{
			UART5_PCCK_EN();
		} else if(pUSARTx == USART6)
		{
			USART6_PCCK_EN();
		}
	}
}

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx;
	uint32_t usartdiv;
	uint32_t M_part,F_part;
	uint32_t tempreg=0;
	// get clock
	if(pUSARTx == USART1 || pUSARTx == USART6)
  {
	   //USART1 and USART6 are hanging on APB2 bus
	   PCLKx = RCC_GetPCLK2Value();
  }else
  {
	   PCLKx = RCC_GetPCLK1Value();
  }
	//Check for OVER8
 if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
  {
	   //OVER8 = 1 , over sampling by 8
	   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
  }else
  {
	   //over sampling by 16
	   usartdiv = ((25 * PCLKx) / (4 *BaudRate));
  }

 // Mantissa
 M_part = usartdiv/100;
 tempreg |= M_part << 4;

 F_part = (usartdiv - (M_part * 100));

 if(pUSARTx->CR1 & ( 1 << USART_CR1_OVER8))
    {
 	  //OVER8 = 1 , over sampling by 8
 	  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);
    }else
    {
 	   //over sampling by 16
 	   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);
    }
  tempreg |= F_part;
  pUSARTx->BRR = tempreg;

}


void USART_Init(USART_Handle_t *pUSARTHandle)
{
	/* temp variable*/
	uint32_t tempreg =0;
	/*enable the Clock*/
	USART_PeriClockControl( pUSARTHandle->pUSARTx, ENABLE);


                                       /*CR1*/
	/*set mode*/
	if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX) /*Rx enable*/
	{
		//Implement the code to enable the Receiver bit field
		tempreg|= (1 << USART_CR1_RE);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		//Implement the code to enable the Transmitter bit field
		tempreg |= ( 1 << USART_CR1_TE );

	}
	else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		//Implement the code to enable the both Transmitter and Receiver bit fields
		tempreg |= ( ( 1 << USART_CR1_RE) | ( 1 << USART_CR1_TE) );
	}

	// Word length
	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;

    	// parity
	if ( pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		//Implement the code to enable the parity control
		tempreg |= ( 1 << USART_CR1_PCE);

	}
	else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD )
	{
		//Implement the code to enable ODD parity
		tempreg |= ( 1 << USART_CR1_PS);

		//Implement the code to enable the parity control
		tempreg |= ( 1 << USART_CR1_PCE);
	}

    pUSARTHandle->pUSARTx->CR1 = tempreg;

                             /*CR2 */
	tempreg =0;

	// stop bit
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;
	pUSARTHandle->pUSARTx->CR2 = tempreg;
   

   	// begin CR3
	tempreg =0;
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//Implement the code to enable CTS flow control
		tempreg |= ( 1 << USART_CR3_CTSE);


	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//Implement the code to enable RTS flow control
		tempreg |= ( 1 << USART_CR3_RTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control
		tempreg |= ( 1 << USART_CR3_CTSE);
		tempreg |= ( 1 << USART_CR3_RTSE);
	}

	pUSARTHandle->pUSARTx->CR3 = tempreg;

    USART_SetBaudRate(pUSARTHandle->pUSARTx,pUSARTHandle->USART_Config.USART_Baud);
}

/*Enable uart*/
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Cmd)
{
	if(Cmd == ENABLE)
	{
		pUSARTx->CR1 |= (1 << 13);
	}
	else
	{
		pUSARTx->CR1 &=~ (1 << 13);
	}
}

/*get flag */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
	uint8_t status = RESET;
	if(pUSARTx->SR & StatusFlagName)
	{
		status = SET;
	}
	return status;
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;
	for(uint32_t i = 0 ; i < Len; i++)
	{
		// wait until TXE flag is set in SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_TXE));

		//Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
            //load the DR with 2bytes
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//bits of user data will be sent 9 bit ( 2 byte )
				pTxBuffer++;
				pTxBuffer++;
			}
			else // USART_PARITY_ENABLE, sent 8 bit
			{
				pTxBuffer++;
			}
		}
		else  // USART_WordLength = 8 bit
		{
			//This is 8bit data transfer
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
			// increment the buffer address
			pTxBuffer++;

		}
	}
}

void  USART_ReceiveData(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	for(uint32_t i =0;i< Len ;i++)
	{
		// wait until RXNE set, Khi buf chưa đủ data thì đợi
		while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_RXNE));

		// check wordlength 8 bit or 9bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			// check parity
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);

				pRxBuffer++;
				pRxBuffer++;
			}
			else  // parity enable  9 bit = 8 bit + 1 parity
			{
				*pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
				 pRxBuffer++;
			}
		}
		else  // 8 bit
		{
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				 *pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
			}
			else
			{
				// 8 bit = 7 bit data + 1 bit parity
				*pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);
			}

			pRxBuffer++;
		}

	}
}

void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
	pUSARTx->SR &= ~( StatusFlagName);

}

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
}

void USART_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{

	uint8_t ipr = IRQNumber /4;
	uint8_t irq = IRQNumber %4;

	*(NVIC_PR_BASE_ADDR + ipr) |= (IRQPriority << (8*irq + 4));
}

uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		//enable interrupt for TXE
		pUSARTHandle->pUSARTx->CR1 |= ( 1 << USART_CR1_TXEIE);

		//enable interrupt for TC
		pUSARTHandle->pUSARTx->CR1 |= ( 1 << USART_CR1_TCIE);
	}

	return txstate;
}

uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->RxBusyState;
	if(rxstate != USART_BUSY_IN_RX)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = pRxBuffer;
		pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

		(void)pUSARTHandle->pUSARTx->DR;

		// enable interrupt for RXNE
		pUSARTHandle->pUSARTx->CR1 |= ( 1 << USART_CR1_RXNEIE);
	}
	return rxstate;
}

void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
	
	uint32_t temp1 , temp2;
	uint16_t *pdata;

	// TC flag
//	check the state of TC bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TC);
//	check the state of TCIE bit
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TCIE);
	if(temp1 && temp2 )
	{
		//interrupt is because of TC
		// if TxLen is zero, close transmit and call application
		if ( pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			if(! pUSARTHandle->TxLen )
			{
				//clear the TC flag
				pUSARTHandle->pUSARTx->SR &= ~( 1 << USART_SR_TC);
				//clear the TCIE control bit
				pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_TCIE);

				pUSARTHandle->TxBusyState = USART_READY;
				pUSARTHandle->pTxBuffer = NULL;
				pUSARTHandle->TxLen = 0;

				// call application
				USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_TX_CMPLT);
			}
		}
	}

	//TXE flag
//	check the state of TXE bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TXE);
//	check the state of TXEIE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TXEIE);
	if(temp1 && temp2 )
	{// interrupt is because of TXE
		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			if(pUSARTHandle->TxLen > 0)
			{
				if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
				{
					pdata = (uint16_t*) pUSARTHandle->pTxBuffer;
					pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);
					if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
					{
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->TxLen-=2;
					}
					else{
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->TxLen-=1;
					}
				}
				else{
					pUSARTHandle->pUSARTx->DR = (*pUSARTHandle->pTxBuffer  & (uint8_t)0xFF);
					pUSARTHandle->pTxBuffer++;
					pUSARTHandle->TxLen-=1;
				}
			}
			if (pUSARTHandle->TxLen == 0 )
			{
				// clear the TXEIE
				pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_TXEIE);
			}
		}
	}


//	RXNE flag
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_RXNE);
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_RXNEIE);
	if(temp1 && temp2 )
	{
		if(pUSARTHandle->RxBusyState == USART_BUSY_IN_RX)
		{
			if(pUSARTHandle->RxLen > 0)
			{
				if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
				{
					if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
					{
						*((uint16_t*) pUSARTHandle->pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->RxLen-=2;
					}
					else{
						 *pUSARTHandle->pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
						 pUSARTHandle->pRxBuffer++;
						 pUSARTHandle->RxLen-=1;
					}
				}
				else{
					if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
					{
						 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
					}
					else{
						 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);
					}
					pUSARTHandle->pRxBuffer++;
					pUSARTHandle->RxLen-=1;
				}
			}
			if(! pUSARTHandle->RxLen)
			{//disable the rxne
				pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_RXNEIE );
				pUSARTHandle->RxBusyState = USART_READY;
				USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_RX_CMPLT);
			}
		}
	}

	// CTS flag
	// not use for UART4 and UART5
	//Implement the code to check the status of CTS bit in the SR
		temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_CTS);
	//Implement the code to check the state of CTSE bit in CR1
		temp2 = pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_CTSE);
		if(temp1  && temp2 )
		{
			//Implement the code to clear the CTS flag in SR
			pUSARTHandle->pUSARTx->SR &=  ~( 1 << USART_SR_CTS);

			//this interrupt is because of cts
			USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_CTS);
		}

		// IDLE detection flag
		//Implement the code to check the status of IDLE flag bit in the SR
		temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_IDLE);

		//Implement the code to check the state of IDLEIE bit in CR1
		temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_IDLEIE);


		if(temp1 && temp2)
		{
			//Implement the code to clear the IDLE flag.
			temp1 = pUSARTHandle->pUSARTx->SR &= ~( 1 << USART_SR_IDLE);

			//this interrupt is because of idle
			USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_IDLE);
		}

		// Overrun detection flag
		//Implement the code to check the status of ORE flag  in the SR
		temp1 = pUSARTHandle->pUSARTx->SR & USART_SR_ORE;

		//Implement the code to check the status of RXNEIE  bit in the CR1
		temp2 = pUSARTHandle->pUSARTx->CR1 & USART_CR1_RXNEIE;
		if(temp1  && temp2 )
		{
			//this interrupt is because of Overrun error
			USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_ORE);
		}

		// Error Flag
		temp2 =  pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_EIE) ;
		if(temp2 )
		{
			temp1 = pUSARTHandle->pUSARTx->SR;
			if(temp1 & ( 1 << USART_SR_FE))
			{
				USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_FE);
			}

			if(temp1 & ( 1 << USART_SR_NE) )
			{
				USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_NE);
			}

			if(temp1 & ( 1 << USART_SR_ORE) )
			{
				USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_ORE);
			}
		}
}












__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t event)
{

}
