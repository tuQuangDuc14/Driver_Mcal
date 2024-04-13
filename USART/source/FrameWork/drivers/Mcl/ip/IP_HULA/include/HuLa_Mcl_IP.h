#ifndef HULA_MCL_IP_H_
#define HULA_MCL_IP_H_

#include "Header.h"

typedef struct
{
	uint32_t Channel;         	  /* Channel */
	uint32_t Direction;	     	    /* M2P, M2M, P2M */
	uint32_t PeriAddrIncre;	   	  /* Tăng địa chỉ hay không */
	uint32_t MemAddrIncre;	 	    /* Tăng địa chỉ hay không */   
	uint32_t PeriDataWidth;       /* Peripheral data width */
	uint32_t MemDataWidth;        /* Memory data width */
	uint32_t Mode;                /* circular/NORMAL/flow control  */
	uint32_t Priority;            /* Priority */
	uint32_t FIFOMode;            /* FIFO mode or Direct mode */
	uint32_t FIFOThreshold;       /* FIFO threshold level */
	uint32_t MemBurst;            /* Truyền riêng lẻ hoặc truyền từng đợt 4,8,16 bit */
	uint32_t PeriBurst;           /* Truyền riêng lẻ hoặc truyền từng đợt 4,8,16 bit */ 
  uint32_t StreamBaseAddress;   /* DMA Stream Base Address */
  uint32_t StreamIndex;         /* DMA Stream Index  */
}MCL_Config_t;

/* DMA State */
typedef enum
{
  DMA_STATE_RESET             = 0x00U,  /* DMA not yet initialized or disabled */
  DMA_STATE_READY             = 0x01U,  /* DMA initialized and ready for use   */
  DMA_STATE_BUSY              = 0x02U,  /* DMA process is ongoing              */
  DMA_STATE_TIMEOUT           = 0x03U,  /* DMA timeout state                   */
  DMA_STATE_ERROR             = 0x04U,  /* DMA error state                     */
  DMA_STATE_ABORT             = 0x05U,  /* DMA Abort state                     */
}MCL_State_t;

typedef struct MCL_Handle
{
	DMA_RegDef_t 	        *pDMAx;     /* DMA Interrupt */
	DMA_Stream_RegDef_t 	*pSTREAMx;
	MCL_Config_t 	        MCLConfig;
	__IO uint32_t         ErrorCode; 
	__IO MCL_State_t      State;
  void (*CpltCallback)( struct MCL_Handle *pMCLHandle);        /* DMA transfer complete callback */
  void (*HalfCpltCallback)( struct MCL_Handle *pMCLHandle);    /* DMA Half transfer complete callbackk */
  void (*M1CpltCallback)( struct MCL_Handle *pMCLHandle);      /* DMA transfer complete Memory1 callback */
  void (*M1HalfCpltCallback)( struct MCL_Handle *pMCLHandle);  /* DMA transfer Half complete Memory1 callback */
  void (*ErrorCallback)( struct MCL_Handle *pMCLHandle);       /* DMA transfer error callback  */
  void (*AbortCallback)( struct MCL_Handle *pMCLHandle);       /* DMA transfer Abort callback */
}MCL_Handle_t;

/* Channel */
#define DMA_CHANNEL_0                 0x00000000U   
#define DMA_CHANNEL_1                 0x02000000U   
#define DMA_CHANNEL_2                 0x04000000U   
#define DMA_CHANNEL_3                 0x06000000U   
#define DMA_CHANNEL_4                 0x08000000U   
#define DMA_CHANNEL_5                 0x0A000000U   
#define DMA_CHANNEL_6                 0x0C000000U   
#define DMA_CHANNEL_7                 0x0E000000U   

/* Direction */ 
#define DMA_PERIPH_TO_MEMORY          0x00000000U                 
#define DMA_MEMORY_TO_PERIPH          ((uint32_t)DMA_SxCR_DIR_0)  
#define DMA_MEMORY_TO_MEMORY          ((uint32_t)DMA_SxCR_DIR_1)  

/* PeriphInc */
#define DMA_PINC_ENABLE               ((uint32_t)DMA_SxCR_PINC)  
#define DMA_PINC_DISABLE              0x00000000U          

/* MemAddrIncre */
#define DMA_MINC_ENABLE               ((uint32_t)DMA_SxCR_MINC) 
#define DMA_MINC_DISABLE              0x00000000U            

/* PeriDataWidth */
#define DMA_PDATAALIGN_BYTE           0x00000000U                  
#define DMA_PDATAALIGN_HALFWORD       ((uint32_t)DMA_SxCR_PSIZE_0) 
#define DMA_PDATAALIGN_WORD           ((uint32_t)DMA_SxCR_PSIZE_1) 

/* MemDataWidth */
#define DMA_MDATAALIGN_BYTE           0x00000000U                 
#define DMA_MDATAALIGN_HALFWORD       ((uint32_t)DMA_SxCR_MSIZE_0)
#define DMA_MDATAALIGN_WORD           ((uint32_t)DMA_SxCR_MSIZE_1)

/* Mode */
#define DMA_NORMAL                    0x00000000U                  
#define DMA_CIRCULAR                  ((uint32_t)DMA_SxCR_CIRC)    

/* Priority */
#define DMA_PRIORITY_LOW              0x00000000U               
#define DMA_PRIORITY_MEDIUM           ((uint32_t)DMA_SxCR_PL_0) 
#define DMA_PRIORITY_HIGH             ((uint32_t)DMA_SxCR_PL_1) 
#define DMA_PRIORITY_VERY_HIGH        ((uint32_t)DMA_SxCR_PL)   

/* FIFOMode */
#define DMA_FIFOMODE_DISABLE          0x00000000U                 
#define DMA_FIFOMODE_ENABLE           ((uint32_t)DMA_SxFCR_DMDIS) 

/* FIFOThreshold */
#define DMA_FIFO_THRESHOLD_1QUARTERFULL       0x00000000U                 
#define DMA_FIFO_THRESHOLD_HALFFULL           ((uint32_t)DMA_SxFCR_FTH_0) 
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL      ((uint32_t)DMA_SxFCR_FTH_1) 
#define DMA_FIFO_THRESHOLD_FULL               ((uint32_t)DMA_SxFCR_FTH)   

/* MemBurst */
#define DMA_MBURST_SINGLE             0x00000000U
#define DMA_MBURST_INC4               ((uint32_t)DMA_SxCR_MBURST_0)  
#define DMA_MBURST_INC8               ((uint32_t)DMA_SxCR_MBURST_1)  
#define DMA_MBURST_INC16              ((uint32_t)DMA_SxCR_MBURST)  

/* PeriBurst */
#define DMA_PBURST_SINGLE             0x00000000U
#define DMA_PBURST_INC4               ((uint32_t)DMA_SxCR_PBURST_0)
#define DMA_PBURST_INC8               ((uint32_t)DMA_SxCR_PBURST_1)
#define DMA_PBURST_INC16              ((uint32_t)DMA_SxCR_PBURST)

/* DMA interrupt enable */
#define DMA_IT_TC                     ((uint32_t)DMA_SxCR_TCIE)
#define DMA_IT_HT                     ((uint32_t)DMA_SxCR_HTIE)
#define DMA_IT_TE                     ((uint32_t)DMA_SxCR_TEIE)
#define DMA_IT_DME                    ((uint32_t)DMA_SxCR_DMEIE)
#define DMA_IT_FE                     0x00000080U

/*DMA flag */ 
#define DMA_FLAG_FEIF0_4              0x00000001U
#define DMA_FLAG_DMEIF0_4             0x00000004U
#define DMA_FLAG_TEIF0_4              0x00000008U
#define DMA_FLAG_HTIF0_4              0x00000010U
#define DMA_FLAG_TCIF0_4              0x00000020U
#define DMA_FLAG_FEIF1_5              0x00000040U
#define DMA_FLAG_DMEIF1_5             0x00000100U
#define DMA_FLAG_TEIF1_5              0x00000200U
#define DMA_FLAG_HTIF1_5              0x00000400U
#define DMA_FLAG_TCIF1_5              0x00000800U
#define DMA_FLAG_FEIF2_6              0x00010000U
#define DMA_FLAG_DMEIF2_6             0x00040000U
#define DMA_FLAG_TEIF2_6              0x00080000U
#define DMA_FLAG_HTIF2_6              0x00100000U
#define DMA_FLAG_TCIF2_6              0x00200000U
#define DMA_FLAG_FEIF3_7              0x00400000U
#define DMA_FLAG_DMEIF3_7             0x01000000U
#define DMA_FLAG_TEIF3_7              0x02000000U
#define DMA_FLAG_HTIF3_7              0x04000000U
#define DMA_FLAG_TCIF3_7              0x08000000U

/* ErrorCode */
#define DMA_ERROR_NONE            0x00000000U    /* No error                               */
#define DMA_ERROR_TE              0x00000001U    /* Transfer error                         */
#define DMA_ERROR_FE              0x00000002U    /* FIFO error                             */
#define DMA_ERROR_DME             0x00000004U    /* Direct Mode error                      */
#define DMA_ERROR_TIMEOUT         0x00000020U    /* Timeout error                          */
#define DMA_ERROR_PARAM           0x00000040U    /* Parameter error                        */
#define DMA_ERROR_NO              0x00000080U    /* Abort requested with no Xfer ongoing   */
#define DMA_ERROR_NOT_SUPPORTED   0x00000100U    /* Not supported mode                     */

/* DMA Error Code */
typedef enum
{
  DMA_CPLT_CB_ID         = 0x00U,  /* Full transfer     */
  DMA_HALFCPLT_CB_ID     = 0x01U,  /* Half Transfer     */
  DMA_M1CPLT_CB_ID       = 0x02U,  /* M1 Full Transfer  */
  DMA_M1HALFCPLT_CB_ID   = 0x03U,  /* M1 Half Transfer  */
  DMA_ERROR_CB_ID        = 0x04U,  /* Error             */
  DMA_ABORT_CB_ID        = 0x05U,  /* Abort             */
  DMA_ALL_CB_ID          = 0x06U   /* All               */
}MCL_CallbackID_t;

void MCL_PeriClockControl(DMA_RegDef_t *pMCLx, uint8_t EnorDi);
uint8_t MCL_Init(MCL_Handle_t *pMCLHandle);
uint8_t MCL_DeInit(MCL_Handle_t *pMCLHandle);

uint8_t MCL_Start(MCL_Handle_t *pMCLHandle, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
uint8_t MCL_Abort(MCL_Handle_t *pMCLHandle);
uint8_t MCL_WaitForTransfer(MCL_Handle_t *pMCLHandle);

uint8_t MCL_Start_IT(MCL_Handle_t *pMCLHandle, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
uint8_t MCL_Abort_IT(MCL_Handle_t *pMCLHandle);
void MCL_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void MCL_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void MCL_IRQHandling(MCL_Handle_t *pMCLHandle);

uint8_t MCL_RegisterCallback(MCL_Handle_t *pMCLHandle, MCL_CallbackID_t CallbackID, void (* pCallback)(MCL_Handle_t *pMCLHandle));
uint8_t MCL_UnRegisterCallback(MCL_Handle_t *pMCLHandle, MCL_CallbackID_t CallbackID);


#endif /* HULA_MCL_IP_H_ */
