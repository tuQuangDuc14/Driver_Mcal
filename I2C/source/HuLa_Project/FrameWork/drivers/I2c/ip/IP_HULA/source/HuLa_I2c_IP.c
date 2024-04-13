#include "HuLa_I2c_IP.h"

static void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
static uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName);


static void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(ENABLE == EnorDi)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}
		else
		{
			I2C2_PCLK_EN();
		}
		else
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();
		}
		else
		{
			I2C2_PCLK_DI();
		}
		else
		{
			I2C3_PCLK_DI();
		}
	}
}

void I2C_CloseSendData(I2C_Handle_t *pI2CHandle)
{
	//Implement the code to disable ITBUFEN Control Bit
	pI2CHandle->pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITBUFEN);

	//Implement the code to disable ITEVFEN Control Bit
	pI2CHandle->pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITEVTEN);


	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->pTxBuffer = NULL;
	pI2CHandle->TxLen = 0;
}

static void I2C_MasterHandleTXEInterrupt(I2C_Handle_t *pI2CHandle )
{

	if(pI2CHandle->TxLen > 0)
	{
		//1. load the data in to DR
		pI2CHandle->pI2Cx->DR = *(pI2CHandle->pTxBuffer);

		//2. decrement the TxLen
		pI2CHandle->TxLen--;

		//3. Increment the buffer address
		pI2CHandle->pTxBuffer++;

	}

}

static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *pI2CHandle )
{
	//We have to do the data reception
	if(pI2CHandle->RxSize == 1)
	{
		*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
		pI2CHandle->RxLen--;

	}


	if(pI2CHandle->RxSize > 1)
	{
		if(pI2CHandle->RxLen == 2)
		{
			//clear the ack bit
			I2C_ManageAcking(pI2CHandle->pI2Cx,DISABLE);
		}

			//read DR
			*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
			pI2CHandle->pRxBuffer++;
			pI2CHandle->RxLen--;
	}

	if(pI2CHandle->RxLen == 0 )
	{
		//close the I2C data reception and notify the application

		//1. generate the stop condition
		if(pI2CHandle->Sr == I2C_DISABLE_SR)
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

		//2 . Close the I2C rx
		I2C_CloseReceiveData(pI2CHandle);

		//3. Notify the application
		I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_RX_CMPLT);
	}
}


static uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle )
{
	uint32_t dummy_read;
	//check for device mode
	if(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_MSL)) /*Set by hardware as soon as the interface is in Master mode (SB=1)*/
	{
		//device is in master mode
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			if(pI2CHandle->RxSize  == 1)
			{
				//first disable the ack
				I2C_ManageAcking(pI2CHandle->pI2Cx,DISABLE);

				//clear the ADDR flag ( read SR1 , read SR2)
				dummy_read = pI2CHandle->pI2Cx->SR1;
				dummy_read = pI2CHandle->pI2Cx->SR2;
				(void)dummy_read; /*đọc ra để clear */
			}
		}
		else
		{
			//clear the ADDR flag ( read SR1 , read SR2)
			dummy_read = pI2CHandle->pI2Cx->SR1;
			dummy_read = pI2CHandle->pI2Cx->SR2;
			(void)dummy_read; /*đọc ra để clear */

		}
	}
	else
	{
		//device is in slave mode
		//clear the ADDR flag ( read SR1 , read SR2)
		dummy_read = pI2CHandle->pI2Cx->SR1;
		dummy_read = pI2CHandle->pI2Cx->SR2;
		(void)dummy_read; /*đọc ra để clear */
	}
}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_ENABLE)
	{
		//enable the ack
		pI2Cx->CR1 |= ( 1 << I2C_CR1_ACK);
	}else
	{
		//disable the ack
		pI2Cx->CR1 &= ~( 1 << I2C_CR1_ACK);
	}
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0 ;

	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);
    
	/*Enable ack*/
	tempreg = pI2CHandle->I2C_Config.I2C_AckControl << 10;
	pI2CHandle->pI2Cx->CR1 = tempreg;

    /*cfg req*/
    tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() /1000000U ; /*vì tính theo Mhz nên /1000000*/
	pI2CHandle->pI2Cx->CR2 =  (tempreg & 0x3F); /*chỉ ghi vào 6 bit đàu tiên*/

    /* OAR1 7 bit or 10 bit - always use 7bit so don't care ADDMODE and ADD0*/ 
	tempreg = 0;
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1; /*Interface address*/
	tempreg |= ( 1 << 14);  //  Should always be kept at 1 by software.
	pI2CHandle->pI2Cx->OAR1 = tempreg;

    /*cfg RRC to Controls the SCL clock in master mode*/
	tempreg = 0;
	uint16_t ccr_value = 0;
    
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_SM) /*standard mode*/
	{
        ccr_value =  (RCC_GetPCLK1Value() / ( 2 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) ); /*tính toán để ghi vào thanh ghi rrc*/
		tempreg |= (ccr_value & 0xFFF);
	}
	else
	{
		tempreg |= ( 1 << 15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);

		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2) /*DUTY = 0*/
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
		}
		else /*DUTY = 1*/
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
		}
		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg;

    /*to keep a stable SCL frequency whatever the SCL rising edge duration*/
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_SM)
	{
        tempreg = (RCC_GetPCLK1Value() /1000000U) + 1;
	}
	{
		tempreg = ( (RCC_GetPCLK1Value() * 300) / 1000000000U ) + 1;
	}
	pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	/*Enable periphral*/
	pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE);

	/*START condition*/
	pI2Cx->CR1 |= ( 1 << I2C_CR1_START);

	/* checking the SB flag in the SR1, SCL = LOW*/
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB)); /* SB Set when a Start condition generated*/
	/*send address data and bit read/write (total 8 bits )*/
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~(1); /*SlaveAddr is Slave address + r/nw bit=0*/
	pI2Cx->DR = SlaveAddr;

	/*checking the ADDR flag in teh SR1 - Address sent (master mode)/matched (slave mode)*/ 
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR));

	/*clear the ADDR flag , SCL = LOW*/
	I2C_ClearADDRFlag(pI2CHandle);

	/*send the data until len becomes 0*/
	while(Len > 0)
	{
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_TXE)); /*Set when DR is empty in transmission*/
		pI2CHandle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		Len--;
	}
    /*when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition*/
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_TXE) );/*Set when DR is empty in transmission*/

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_BTF) );/*set when Data byte transfer succeeded*/
    
	/*STop condition*/
	pI2Cx->CR1 |= ( 1 << I2C_CR1_STOP);
}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	/*Enable periphral*/
	pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE);

	/*START condition*/
	pI2Cx->CR1 |= ( 1 << I2C_CR1_START);

	/* checking the SB flag in the SR1, SCL = LOW*/
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB)); /* SB Set when a Start condition generated*/
	/*send address data and bit read/write (total 8 bits )*/
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr |= 1; /*SlaveAddr is Slave address + r/nw bit=0*/
	pI2Cx->DR = SlaveAddr;

	/*checking the ADDR flag in teh SR1 - Address sent (master mode)/matched (slave mode)*/ 
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR));
    
	if(Len ==1)
	{
        /*disable ack*/
	    pI2Cx->CR1 &= ~( 1 << I2C_CR1_ACK); /*NACK will be sent to the slave*/
		/*clear the ADDR flag , SCL = LOW*/
	    I2C_ClearADDRFlag(pI2CHandle);
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_RXNE)); /*Data register not empty*/
		/*STop condition*/
	    pI2Cx->CR1 |= ( 1 << I2C_CR1_STOP);
		/*read data*/
		*pRxBuffer = pI2CHandle->pI2Cx->DR;
	}
    if(Len >1)  
	{
		/*clear the ADDR flag , SCL = LOW*/
	    I2C_ClearADDRFlag(pI2CHandle);
		/*read the data until Len becomes zero*/
		for ( uint32_t i = Len ; i > 0 ; i--)
		{
			/*wait until RXNE becomes 1*/
			while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_RXNE));
			if(Len == 2)
			{
				pI2Cx->CR1 &= ~( 1 << I2C_CR1_ACK); /*NACK will be sent to the slave*/
				/*STop condition*/
	            pI2Cx->CR1 |= ( 1 << I2C_CR1_STOP);
			}
			/*read the data from data register in to buffer*/
			*pRxBuffer = pI2CHandle->pI2Cx->DR;
			pRxBuffer++;
		}

	}
}

void I2C_SlaveSendData(I2C_RegDef_t *pI2C,uint8_t data)
{
	pI2C->DR = data;
}

uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2C)
{
    return (uint8_t) pI2C->DR;
}

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
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
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
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
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}

}

void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	uint8_t ipr = IRQNumber /4;
	uint8_t irq = IRQNumber %4;

	*(NVIC_PR_BASE_ADDR + ipr) |= (IRQPriority << (8*irq + 4));
}

uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	/*khi start condition thì sẽ sinh ra các event và nhảy vào hadling để tiếp tục xử lí*/
	uint8_t busystate = pI2CHandle->TxRxState;
	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer = pTxBuffer;
		pI2CHandle->TxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

	    /*START condition*/
	    pI2Cx->CR1 |= ( 1 << I2C_CR1_START);
        /*Enable tất cả các ngắt*/
		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);
	}
	return busystate;
}

uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer = pRxBuffer;
		pI2CHandle->RxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize = Len;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

	    /*START condition*/
	    pI2Cx->CR1 |= ( 1 << I2C_CR1_START);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);
	}

	return busystate;
}

void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle)
{
   /*Interrupt handling for both master and slave mode of a device*/
   uint32_t temp1, temp2, temp3;

   temp1 = pI2CHandle->pI2Cx->CR2 & ( 1 << I2C_CR2_ITEVTEN); /*Event interrupt enable*/
   temp2   = pI2CHandle->pI2Cx->CR2 & ( 1 << I2C_CR2_ITBUFEN); /*Buffer interrupt enable*/

   temp3  = pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_SB);/*Set when a Start condition generated.*/
   /*SB flag*/
   if(temp1 && temp3)
   {
	   if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
	   {
          I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,pI2CHandle->DevAddr);
	   }
	   else
	   {
		I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,pI2CHandle->DevAddr);
	   }
   }

   	temp3 =0;
    temp3  = pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_ADDR);
	/*ADDR event*/
	/*When master mode : Address is sent*/
	/*When Slave mode   : Địa chỉ khớp với địa chỉ riêng*/ 
	if(temp1 && temp3)
	{
		/*Interrupt is generated because of ADDR event*/
		I2C_ClearADDRFlag(pI2CHandle);
	}

    temp3 =0;
	temp3  = pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_BTF);/*BTF(Byte Transfer Finished)*/
	if(temp1 && temp3)
	{
		/*BTF flag is set*/
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			//make sure that TXE is also set .
			if(pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_TXE) )
			{
				//BTF, TXE = 1
				if(pI2CHandle->TxLen == 0 )
				{
					//1. generate the STOP condition
					if(pI2CHandle->Sr == I2C_DISABLE_SR)
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

					//2. reset all the member elements of the handle structure.
					I2C_CloseSendData(pI2CHandle);

					//3. notify the application about transmission complete
					I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_TX_CMPLT);
				}
			}
		}else if (pI2CHandle->TxRxState == I2C_BUSY_IN_RX )
		{
			;
		}
	}

	temp3  = pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_STOPF);
	if(temp1 && temp3)
	{
		//STOF flag is set
		//Clear the STOPF

		pI2CHandle->pI2Cx->CR1 |= 0x0000;

		//Notify the application that STOP is detected
		I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_STOP);
	}

	temp3  = pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_TXE);/*transmit*/
	if(temp1 && temp2 && temp3)
	{
		//Check for device mode
		if(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_MSL))
		{
			//TXE flag is set
			//i have to do the data transmission
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
			{
				I2C_MasterHandleTXEInterrupt(pI2CHandle);
			}
		}else
		{
			//slave
			//make sure that the slave is really in transmitter mode
			if(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_TRA))
			{
				I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_DATA_REQ);
			}
		}
	}

	temp3  = pI2CHandle->pI2Cx->SR1 & ( 1 << I2C_SR1_RXNE);
	if(temp1 && temp2 && temp3)
	{
		//check device mode .
		if(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_MSL))
		{
			//The device is master

			//RXNE flag is set
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
			{
				I2C_MasterHandleRXNEInterrupt(pI2CHandle);

			}

		}else
		{
			//slave
			//make sure that the slave is really in receiver mode
			if(!(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_TRA)))
			{
				I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_DATA_RCV);
			}
		}
	}
}

void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	uint32_t temp1,temp2;
	//	ITERREN control bit
	temp2 = (pI2CHandle->pI2Cx->CR2) & ( 1 << I2C_CR2_ITERREN);

	//Check for Bus error
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1<< I2C_SR1_BERR);
	if(temp1  && temp2 )
	{
		//This is Bus error

		//Implement the code to clear the buss error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_BERR);

		//Implement the code to notify the application about the error
	   I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_BERR);
	}

	//Check for arbitration lost error
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_ARLO );
	if(temp1  && temp2)
	{
		//This is arbitration lost error

		//Implement the code to clear the arbitration lost error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_ARLO);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_ARLO);
	}

	//Check for ACK failure  error
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_AF);
	if(temp1  && temp2)
	{
		//This is ACK failure error

		//Implement the code to clear the ACK failure error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_AF);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_AF);
	}

//	Check for Overrun/underrun error
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_OVR);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun

		//Implement the code to clear the Overrun/underrun error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_OVR);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_OVR);
	}

//	Check for Time out error
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_TIMEOUT);
	if(temp1  && temp2)
	{
		//This is Time out error

		//Implement the code to clear the Time out error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_TIMEOUT);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_TIMEOUT);
	}
}


__attribute__((weak)) void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv)
{

}