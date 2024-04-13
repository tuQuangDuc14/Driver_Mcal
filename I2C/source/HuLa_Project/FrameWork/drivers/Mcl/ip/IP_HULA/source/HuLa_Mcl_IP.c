#include "HuLa_Mcl_IP.h"

/* Return base address phụ thuộc vào stream number */
static uint32_t DMA_CalcBaseAddress(MCL_Handle_t *pMCLHandle)
{
    /* Có 8 Stream từ 0-7 */
    uint32_t Stream_Number = (((uint32_t)pMCLHandle->pSTREAMx & 0xFFU) - 16U) / 24U;
  
    /* Table tra cứu các bitshift của flags trong status registers */
    /* Index của Stream x FIFO error interrupt */
    static const uint8_t FlagBitShiftOffset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
    pMCLHandle->MCLConfig.StreamIndex = FlagBitShiftOffset[Stream_Number];
    
    if (Stream_Number > 3U)
    {
        /* return pointer to HISR and HIFCR */
        /* +4 do DMA_HISR có offset là 4*/
        pMCLHandle->MCLConfig.StreamBaseAddress = (((uint32_t)pMCLHandle->pSTREAMx & (uint32_t)(~0x3FFU)) + 4U);
    }
    else
    {
        /* return pointer to LISR and LIFCR */
        /* không cộng do DMA_LISR có offset là 0*/
        pMCLHandle->MCLConfig.StreamBaseAddress = ((uint32_t)pMCLHandle->pSTREAMx & (uint32_t)(~0x3FFU));
    }
    
    return pMCLHandle->MCLConfig.StreamBaseAddress;
}
static uint8_t MCL_CheckFifo_Threshold(MCL_Handle_t *pMCLHandle)
{
    uint32_t TempReg = pMCLHandle->MCLConfig.FIFOThreshold;

    /* Memory Data size equal to Byte */
    if(pMCLHandle->MCLConfig.MemDataWidth == DMA_MDATAALIGN_BYTE)
    {
        switch (TempReg)
        {
            case DMA_FIFO_THRESHOLD_1QUARTERFULL:
            case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
            /* FIFI có độ dài 4 WORD */
                if ((pMCLHandle->MCLConfig.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
                {
                    return 0;
                }
            case DMA_FIFO_THRESHOLD_HALFFULL:
                if (pMCLHandle->MCLConfig.MemBurst == DMA_MBURST_INC16)
                {
                    return 0;
                }
            case DMA_FIFO_THRESHOLD_FULL:
                break;
            default:
                break;
        }
    }
    
    /* Memory Data size equal to Half-Word */
    else if (pMCLHandle->MCLConfig.MemDataWidth == DMA_MDATAALIGN_HALFWORD)
    {
        switch (TempReg)
        {
            case DMA_FIFO_THRESHOLD_1QUARTERFULL:
            case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
                return 0;
            case DMA_FIFO_THRESHOLD_HALFFULL:
            if ((pMCLHandle->MCLConfig.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
            {
                return 0;
            }
            case DMA_FIFO_THRESHOLD_FULL:
            if (pMCLHandle->MCLConfig.MemBurst == DMA_MBURST_INC16)
            {
                return 0;
            }  
            default:
                break;
        }
    }
    
    /* Memory Data size equal to Word */
    else
    {
        switch (TempReg)
        {
            case DMA_FIFO_THRESHOLD_1QUARTERFULL:
            case DMA_FIFO_THRESHOLD_HALFFULL:
            case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
                return 0;
            break;
            case DMA_FIFO_THRESHOLD_FULL:
            if ((pMCLHandle->MCLConfig.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
            {
                return 0;
            }
            default:
                break;
        }
    } 
    
    return 1; 
}

void MCL_PeriClockControl(DMA_RegDef_t *pMCLx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
	{
		if(pMCLx == DMA1)
		{
			DMA1_PCLK_EN();
		}else if (pMCLx == DMA2)
		{
			DMA2_PCLK_EN();
		}
	}
    else
    {
        if(pMCLx == DMA1)
		{
			DMA1_PCLK_DI();
		}else if (pMCLx == DMA2)
		{
			DMA2_PCLK_DI();
		}
    }
}

/* Struct để chứa base address của interrup stream x */
typedef struct
{
  __IO uint32_t ISR;        /* DMA interrupt status register */
  __IO uint32_t Reserved0;  /* Ví dụ là Low thì : DMA_LISR - DMA_HISR - DMA_LIFCR   nên bỏ thằng DMA_HISR đi */
  __IO uint32_t IFCR;       /* DMA interrupt flag clear register */
} DMA_Base_Registers_t;

uint8_t MCL_Init(MCL_Handle_t *pMCLHandle)
{
    uint32_t TmpReg = 0U;
    DMA_Base_Registers_t  *Register;

    /* Change DMA state */
    pMCLHandle->State = DMA_STATE_BUSY;

    /* Disable DMA Stream. */
    pMCLHandle->pSTREAMx->CR &=~ DMA_SxCR_EN;

/******************************** BEGIN CR REGISTER ******************************************/

    /* Get CR register value */
    TmpReg = pMCLHandle->pSTREAMx->CR;

    /* Clear CR Register */
    TmpReg &= ((uint32_t)~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST |  DMA_SxCR_PL    | DMA_SxCR_MSIZE  | DMA_SxCR_PSIZE  | \
                           DMA_SxCR_MINC  | DMA_SxCR_PINC   | DMA_SxCR_CIRC   | DMA_SxCR_DIR    | DMA_SxCR_CT     | DMA_SxCR_DBM));
    
/********************************** Set DMA Stream *******************************************/
    /* Set Channel */
    TmpReg |= pMCLHandle->MCLConfig.Channel;
    /* Set Direction */
    TmpReg |= pMCLHandle->MCLConfig.Direction;
    /* Set PeriAddrIncre */
    TmpReg |= pMCLHandle->MCLConfig.PeriAddrIncre;
    /* Set MemAddrIncre */
    TmpReg |= pMCLHandle->MCLConfig.MemAddrIncre;
    /* Set PeriDataWidth */
    TmpReg |= pMCLHandle->MCLConfig.PeriDataWidth;
    /* Set MemDataWidth */
    TmpReg |= pMCLHandle->MCLConfig.MemDataWidth;
    /* Set Mode */
    TmpReg |= pMCLHandle->MCLConfig.Mode;
    /* Set Priority */
    TmpReg |= pMCLHandle->MCLConfig.Priority;

    /* Memory burst và peripheral burst không được sử dụng khi FIFO disabled */
    if(pMCLHandle->MCLConfig.FIFOMode == DMA_FIFOMODE_ENABLE)
    {
        /* Set MemBurst */
        TmpReg |=  pMCLHandle->MCLConfig.MemBurst ;
        /* Set PeriBurst */
        TmpReg |=  pMCLHandle->MCLConfig.PeriBurst;
    }

    /* Write to DMA Stream CR register */
    pMCLHandle->pSTREAMx->CR = TmpReg;  

/******************************** END CR REGISTER ******************************************/

/******************************** BEGIN FCR REGISTER ******************************************/
    /* Get FCR register value */
    TmpReg = pMCLHandle->pSTREAMx->FCR;

    /* Clear Direct mode và FIFO threshold bits */
    TmpReg &= (uint32_t)~(DMA_SxFCR_DMDIS);
    TmpReg &= (uint32_t)~(DMA_SxFCR_FTH);

    /* DMA Stream FIFO Mode */
    TmpReg |= pMCLHandle->MCLConfig.FIFOMode;

    /* FIFO threshold không được sử dụng khi FIFO disabled */
    if(pMCLHandle->MCLConfig.FIFOMode == DMA_FIFOMODE_ENABLE)
    {
        /* Get the FIFO threshold */
        TmpReg |= pMCLHandle->MCLConfig.FIFOThreshold;

        /* Check size của FIFO threshold level và memory burst có tương thích hay không */
        if (pMCLHandle->MCLConfig.MemBurst != DMA_MBURST_SINGLE)
        {
            if (MCL_CheckFifo_Threshold(pMCLHandle) == 0)
            {
                /* Update error code */
                pMCLHandle->ErrorCode = DMA_ERROR_PARAM;
                
                /* Change the DMA state */
                pMCLHandle->State = DMA_STATE_READY;
                
                return 0; 
            }
        }
    }
    /* Write to DMA Stream FCR */
    pMCLHandle->pSTREAMx->FCR = TmpReg;

/******************************** END FCR REGISTER ******************************************/

/******************************** Initialize StreamBaseAddress and StreamIndex ******************************************/

    /* get base address cho MCL_WaitForTransfer() */
    Register = (DMA_Base_Registers_t *)DMA_CalcBaseAddress(pMCLHandle);

    /* Clear all interrupt flags */
    Register->IFCR |= 0x3FU << pMCLHandle->MCLConfig.StreamIndex;

    /* Initialize the error code */
    pMCLHandle->ErrorCode = DMA_ERROR_NONE;
                                                                                        
    /* Initialize the DMA state */
    pMCLHandle->State = DMA_STATE_READY;

    return 1;
}

uint8_t MCL_DeInit(MCL_Handle_t *pMCLHandle)
{
    DMA_Base_Registers_t  *Register;
    /* Reset DMA Streamx control register */
    pMCLHandle->pSTREAMx->CR   = 0U;

    /* Reset DMA Streamx number of data to transfer register */
    pMCLHandle->pSTREAMx->NDTR = 0U;

    /* Reset DMA Streamx peripheral address register */
    pMCLHandle->pSTREAMx->PAR  = 0U;

    /* Reset DMA Streamx memory 0 address register */
    pMCLHandle->pSTREAMx->M0AR = 0U;
    
    /* Reset DMA Streamx memory 1 address register */
    pMCLHandle->pSTREAMx->M1AR = 0U;

    /* Reset DMA Streamx FIFO control register */
    pMCLHandle->pSTREAMx->FCR  = 0x00000021U;

    Register = (DMA_Base_Registers_t *)DMA_CalcBaseAddress(pMCLHandle);

    /* Clear all interrupt flags at correct offset within the register */
    Register->IFCR |= 0x3FU << pMCLHandle->MCLConfig.StreamIndex;

    /* Reset the error code */
    pMCLHandle->ErrorCode = DMA_ERROR_NONE;

    /* Reset the DMA state */
    pMCLHandle->State = DMA_STATE_RESET;

    /* Clean all callbacks */
    pMCLHandle->AbortCallback=NULL;
    pMCLHandle->CpltCallback=NULL;
    pMCLHandle->ErrorCallback=NULL;
    pMCLHandle->HalfCpltCallback=NULL;
    pMCLHandle->M1CpltCallback=NULL;
    pMCLHandle->M1HalfCpltCallback=NULL;

    return 1;
}

uint8_t MCL_Start(MCL_Handle_t *pMCLHandle, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
    uint8_t Status = 1;

    if(DMA_STATE_READY == pMCLHandle->State)
    {
        /* Change DMA peripheral state */
        pMCLHandle->State = DMA_STATE_BUSY;
        
/************************************* BEGIN Configure the source, destination address and data length *********************/
        /* Clear DBM bit */
        pMCLHandle->pSTREAMx->CR &= (uint32_t)(~DMA_SxCR_DBM);

        /* Configure DMA Stream data length */
        pMCLHandle->pSTREAMx->NDTR = DataLength;

        /* Memory to Peripheral */
        if(pMCLHandle->MCLConfig.Direction == DMA_MEMORY_TO_PERIPH)
        {
            /* Configure DMA Stream destination address */
            pMCLHandle->pSTREAMx->PAR = DstAddress;

            /* Configure DMA Stream source address */
            pMCLHandle->pSTREAMx->M0AR = SrcAddress;
        }
        /* Peripheral to Memory */
        else
        {
            /* Configure DMA Stream source address */
            pMCLHandle->pSTREAMx->PAR = SrcAddress;

            /* Configure DMA Stream destination address */
            pMCLHandle->pSTREAMx->M0AR = DstAddress;
        }
/************************************* END Configure the source, destination address and data length *********************/
        /* Enable Peripheral */
        pMCLHandle->pSTREAMx->CR |= DMA_SxCR_EN;
    }
    else
    { 
        Status = 0;
    } 
    return Status; 
}

/* Nếu 1 data đang truyền thì data hiện tại đó vẫn truyền tiếp khi nào data đó xong thì mới Abort*/
uint8_t MCL_Abort(MCL_Handle_t *pMCLHandle)
{
    /* Calculate DMA base and stream number */
    DMA_Base_Registers_t *Register = (DMA_Base_Registers_t *)pMCLHandle->MCLConfig.StreamBaseAddress;

    if(pMCLHandle->State != DMA_STATE_BUSY)
    {
        pMCLHandle->ErrorCode = DMA_ERROR_NO;
        return 0;
    }
    else 
    {
        /* Disable all the transfer interrupts */
        pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_TC); 
        pMCLHandle->pSTREAMx->FCR &= ~(DMA_IT_FE);
        pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_HT);
        pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_TE);
        pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_DME);
        
        /* Disable the DMA stream */
        pMCLHandle->pSTREAMx->CR &=~ DMA_SxCR_EN;
        
        /* Clear all interrupt flags */
        Register->IFCR |= 0x3FU << pMCLHandle->MCLConfig.StreamIndex;
        
        /* Change the DMA state*/
        pMCLHandle->State = DMA_STATE_READY;
    }

    return 1;
}

uint8_t MCL_WaitForTransfer(MCL_Handle_t *pMCLHandle)
{
    uint8_t Status = 1; 
    uint32_t Mask_CpltLevel;
    uint32_t TmpISR;

    /* Calculate DMA base and stream number */
    DMA_Base_Registers_t *Register = (DMA_Base_Registers_t *)pMCLHandle->MCLConfig.StreamBaseAddress;

    if(DMA_STATE_BUSY != pMCLHandle->State)
    {
        /* No transfer ongoing */
        pMCLHandle->ErrorCode = DMA_ERROR_NO;
        return 0;
    }

    /* Không dùng ở chế độ circular mode */
    if ((pMCLHandle->pSTREAMx->CR & DMA_SxCR_CIRC) != RESET)
    {
        pMCLHandle->ErrorCode = DMA_ERROR_NOT_SUPPORTED;
        return 0;
    }

/********************** Get the level transfer complete flag ****************************8*/

    /* Transfer Complete flag */
    Mask_CpltLevel = DMA_FLAG_TCIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
    TmpISR = Register->ISR;
    if(((TmpISR & Mask_CpltLevel) == RESET) && ((pMCLHandle->ErrorCode & DMA_ERROR_TE) == RESET))
    {
        /* Get the ISR register value */
        TmpISR = Register->ISR;

        if((TmpISR & (DMA_FLAG_TEIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
        {
            /* Update error code */
            pMCLHandle->ErrorCode |= DMA_ERROR_TE;
            
            /* Clear the transfer error flag */
            Register->IFCR |= DMA_FLAG_TEIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
            /* Clear the half transfer and transfer complete flags */
            Register->IFCR |= (DMA_FLAG_HTIF0_4) << pMCLHandle->MCLConfig.StreamIndex;
            Register->IFCR |= (DMA_FLAG_TCIF0_4) << pMCLHandle->MCLConfig.StreamIndex;
        }
        
        if((TmpISR & (DMA_FLAG_FEIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
        {
            /* Update error code */
            pMCLHandle->ErrorCode |= DMA_ERROR_FE;
            
            /* Clear the FIFO error flag */
            Register->IFCR |= DMA_FLAG_FEIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
        }
        
        if((TmpISR & (DMA_FLAG_DMEIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
        {
            /* Update error code */
            pMCLHandle->ErrorCode |= DMA_ERROR_DME;
            
            /* Clear the Direct Mode error flag */
            Register->IFCR |= DMA_FLAG_DMEIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
        }
    }
    
    /* Nếu có lỗi thì Abort luôn */
    if(pMCLHandle->ErrorCode != DMA_ERROR_NONE)
    {
        MCL_Abort(pMCLHandle);
        
        /* Change the DMA state */
        pMCLHandle->State= DMA_STATE_READY;

        return 0;
    }
    
    /* Clear the half transfer and transfer complete flags */
    Register->IFCR |= (DMA_FLAG_HTIF0_4) << pMCLHandle->MCLConfig.StreamIndex;
    Register->IFCR |= (DMA_FLAG_TCIF0_4) << pMCLHandle->MCLConfig.StreamIndex;
    
    pMCLHandle->State = DMA_STATE_READY;
    
    return Status;
}

/*******************************************************************************************/
/********************************************* INTERRUPTS **********************************/
/*******************************************************************************************/

uint8_t MCL_Start_IT(MCL_Handle_t *pMCLHandle, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
    uint8_t Status = 1;
    /* calculate DMA base and stream number */
    DMA_Base_Registers_t *Register = (DMA_Base_Registers_t *)pMCLHandle->MCLConfig.StreamBaseAddress;

    if(DMA_STATE_READY == pMCLHandle->State)
    {
        /* Change DMA peripheral state */
        pMCLHandle->State = DMA_STATE_BUSY;
        
        /* Initialize the error code */
        pMCLHandle->ErrorCode = DMA_ERROR_NONE;
        
/************************************* BEGIN Configure the source, destination address and data length *********************/
        /* Clear DBM bit */
        pMCLHandle->pSTREAMx->CR &= (uint32_t)(~DMA_SxCR_DBM);

        /* Configure DMA Stream data length */
        pMCLHandle->pSTREAMx->NDTR = DataLength;

        /* Memory to Peripheral */
        if(pMCLHandle->MCLConfig.Direction == DMA_MEMORY_TO_PERIPH)
        {
            /* Configure DMA Stream destination address */
            pMCLHandle->pSTREAMx->PAR = DstAddress;

            /* Configure DMA Stream source address */
            pMCLHandle->pSTREAMx->M0AR = SrcAddress;
        }
        /* Peripheral to Memory */
        else
        {
            /* Configure DMA Stream source address */
            pMCLHandle->pSTREAMx->PAR = SrcAddress;

            /* Configure DMA Stream destination address */
            pMCLHandle->pSTREAMx->M0AR = DstAddress;
        }
/************************************* END Configure the source, destination address and data length *********************/
        /* Clear all interrupt flags at correct offset within the register */
        Register->IFCR = 0x3FU << pMCLHandle->MCLConfig.StreamIndex;
        
        /* Enable Common interrupts*/
        pMCLHandle->pSTREAMx->CR  |= DMA_IT_TC ;
        pMCLHandle->pSTREAMx->CR  |= DMA_IT_TE ;
        pMCLHandle->pSTREAMx->CR  |= DMA_IT_DME ;
        pMCLHandle->pSTREAMx->CR  |= DMA_IT_HT ;
        pMCLHandle->pSTREAMx->CR  |= DMA_IT_HT;
        
        /* Enable the Peripheral */
        pMCLHandle->pSTREAMx->CR |= DMA_SxCR_EN;
    }
    else
    { 
        Status = 0;
    }
    return Status; 
}

uint8_t MCL_Abort_IT(MCL_Handle_t *pMCLHandle)
{
    if(pMCLHandle->State != DMA_STATE_BUSY)
    {
        pMCLHandle->ErrorCode = DMA_ERROR_NO;
        return 0;
    }
    else
    {
        /* Set Abort State  */
        pMCLHandle->State = DMA_STATE_ABORT;
        
        /* Disable the stream */
        pMCLHandle->pSTREAMx->CR &=~ DMA_SxCR_EN;
    }

    return 1;
}

void MCL_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			/* program ISER0 register */
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 ) /*32 to 63*/
		{
			/* program ISER1 register */
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			/* program ISER2 register //64 to 95 */
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			/*program ICER0 register*/
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			/*program ICER1 register*/
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			/*program ICER2 register*/
			*NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
}
void MCL_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t ipr = IRQNumber /4;
	uint8_t irq = IRQNumber %4;

	*(NVIC_PR_BASE_ADDR + ipr) |= (IRQPriority << (8*irq + 4));
}

void MCL_IRQHandling(MCL_Handle_t *pMCLHandle)
{
    /* calculate DMA base and stream number */
    DMA_Base_Registers_t *Register = (DMA_Base_Registers_t *)pMCLHandle->MCLConfig.StreamBaseAddress;
    uint32_t TmpISR;

    TmpISR = Register->ISR;

/* Transfer Error Interrupt */
    if ((TmpISR & (DMA_FLAG_TEIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
    {
        /* Cờ ngắt TEIE được set */
        if((pMCLHandle->pSTREAMx->CR & DMA_IT_TE) != RESET)
        {
            /* Disable the transfer error interrupt */
            pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_TE);
            
            /* Clear the transfer error flag */
            Register->IFCR |= DMA_FLAG_TEIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
            
            /* Update error code */
            pMCLHandle->ErrorCode |= DMA_ERROR_TE;
        }
    }
/* FIFO Error Interrupt */
    if ((TmpISR & (DMA_FLAG_FEIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
    {   
        /* Nếu enable FEIE - FIFO error interrupt enable */
        if((pMCLHandle->pSTREAMx->FCR & DMA_IT_FE) != RESET)
        {
            /* Clear the FIFO error flag */
            Register->IFCR |= DMA_FLAG_FEIF0_4 << pMCLHandle->MCLConfig.StreamIndex;

            /* Update error code */
            pMCLHandle->ErrorCode |= DMA_ERROR_FE;
        }
    }
/* Direct Mode Error Interrupt */
    if ((TmpISR & (DMA_FLAG_DMEIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
    {
        if((pMCLHandle->pSTREAMx->CR & DMA_IT_DME) != RESET)
        {
            /* Clear the direct mode error flag */
            Register->IFCR |= DMA_FLAG_DMEIF0_4 << pMCLHandle->MCLConfig.StreamIndex;

            /* Update error code */
            pMCLHandle->ErrorCode |= DMA_ERROR_DME;
        }
    }
/* Half Transfer Complete Interrupt */
    if ((TmpISR & (DMA_FLAG_HTIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
    {
        /* if cờ HTIE set*/
        if((pMCLHandle->pSTREAMx->CR & DMA_IT_HT) != RESET)
        {
            /* Clear the half transfer complete flag */
            Register->IFCR |= DMA_FLAG_HTIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
        
            if(pMCLHandle->HalfCpltCallback != NULL)
            {
                pMCLHandle->HalfCpltCallback(pMCLHandle);
            }
        }
    }
/* Transfer Complete Interrupt */
    if ((TmpISR & (DMA_FLAG_TCIF0_4 << pMCLHandle->MCLConfig.StreamIndex)) != RESET)
    {   
        /* Cờ TCIE được set*/
        if((pMCLHandle->pSTREAMx->CR & DMA_IT_TC) != RESET)
        {
            /* Clear the transfer complete flag */
            Register->IFCR = DMA_FLAG_TCIF0_4 << pMCLHandle->MCLConfig.StreamIndex;
            
            if(DMA_STATE_ABORT == pMCLHandle->State)
            {
                /* Disable all the transfer interrupts */
                pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_TC); 
                pMCLHandle->pSTREAMx->FCR &= ~(DMA_IT_FE);
                pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_HT);
                pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_TE);
                pMCLHandle->pSTREAMx->CR  &= ~(DMA_IT_DME);

                /* Clear all interrupt flags */
                Register->IFCR = 0x3FU << pMCLHandle->MCLConfig.StreamIndex;

                /* Change the DMA state */
                pMCLHandle->State = DMA_STATE_READY;

                if(pMCLHandle->AbortCallback != NULL)
                {
                    pMCLHandle->AbortCallback(pMCLHandle);
                }

                return;
            }

            if(pMCLHandle->CpltCallback != NULL)
            {
                pMCLHandle->CpltCallback(pMCLHandle);
            }
        }
    }
    
/*  Error  */
    if(pMCLHandle->ErrorCode != DMA_ERROR_NONE)
    {
        if((pMCLHandle->ErrorCode & DMA_ERROR_TE) != RESET)
        {
            pMCLHandle->State = DMA_STATE_ABORT;

            /* Disable the stream */
            pMCLHandle->pSTREAMx->CR &=~ DMA_SxCR_EN;

            /* Change the DMA state */
            pMCLHandle->State = DMA_STATE_READY;
        }

        if(pMCLHandle->ErrorCallback != NULL)
        {
            pMCLHandle->ErrorCallback(pMCLHandle);
        }
    }
}

uint8_t MCL_RegisterCallback(MCL_Handle_t *pMCLHandle, MCL_CallbackID_t CallbackID, void (* pCallback)(MCL_Handle_t *pMCLHandle))
{
    uint8_t Status = 1;
    if( DMA_STATE_READY == pMCLHandle->State)
    {
        if(CallbackID == DMA_CPLT_CB_ID)
        {
            pMCLHandle->CpltCallback = pCallback;
        }
        else if(CallbackID == DMA_HALFCPLT_CB_ID)
        {
            pMCLHandle->HalfCpltCallback = pCallback;
        }
        else if(CallbackID == DMA_M1CPLT_CB_ID)
        {
            pMCLHandle->M1CpltCallback = pCallback;
        }
        else if(CallbackID == DMA_M1HALFCPLT_CB_ID)
        {
            pMCLHandle->M1HalfCpltCallback = pCallback;
        }
        else if(CallbackID == DMA_ERROR_CB_ID)
        {
            pMCLHandle->ErrorCallback = pCallback;
        }
        else if(CallbackID == DMA_ABORT_CB_ID)
        {
            pMCLHandle->AbortCallback = pCallback;
        }
    }
    else
    {
        Status = 0;
    }

    return Status;
}
uint8_t MCL_UnRegisterCallback(MCL_Handle_t *pMCLHandle, MCL_CallbackID_t CallbackID)
{
    uint8_t Status = 1;
    if( DMA_STATE_READY == pMCLHandle->State)
    {
        if(CallbackID == DMA_CPLT_CB_ID)
        {
            pMCLHandle->CpltCallback = NULL;
        }
        else if(CallbackID == DMA_HALFCPLT_CB_ID)
        {
            pMCLHandle->HalfCpltCallback = NULL;
        }
        else if(CallbackID == DMA_M1CPLT_CB_ID)
        {
            pMCLHandle->M1CpltCallback = NULL;
        }
        else if(CallbackID == DMA_M1HALFCPLT_CB_ID)
        {
            pMCLHandle->M1HalfCpltCallback = NULL;
        }
        else if(CallbackID == DMA_ERROR_CB_ID)
        {
            pMCLHandle->ErrorCallback = NULL;
        }
        else if(CallbackID == DMA_ABORT_CB_ID)
        {
            pMCLHandle->AbortCallback = NULL;
        }
    }
    else
    {
        Status = 0;
    }

    return Status;
}