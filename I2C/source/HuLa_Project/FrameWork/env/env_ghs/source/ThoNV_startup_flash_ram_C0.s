
.section ".init_table", "a"
  .long VECTORTABLE_START
  .long INIT_VECTORTABLE_START
  .long INIT_VECTORTABLE_END
  .long DATA_START
  .long INIT_DATA_START
  .long INIT_DATA_END
  .long DATA_NOCACHE_START
  .long INIT_DATA_NOCACHE_START
  .long INIT_DATA_NOCACHE_END
  .long DATA_SHAREABLE_START
  .long INIT_DATA_SHAREABLE_START
  .long INIT_DATA_SHAREABLE_END

.section ".zero_table", "a"
  .long BSS_START
  .long BSS_END
  .long BSS_NOCACHE_START
  .long BSS_NOCACHE_END
  .long BSS_SHAREABLE_START
  .long BSS_SHAREABLE_END

.section ".intc_vector","ax"
.align 2
.thumb
.globl undefined_handler
.globl undefined_handler
.globl Stack_start_c0
.globl Reset_Handler
.globl VTABLE
.globl NMI_Handler
.globl HardFault_Handler
.globl MemManage_Handler
.globl BusFault_Handler
.globl UsageFault_Handler
.globl SVC_Handler
.globl DebugMon_Handler
.globl PendSV_Handler
.globl SysTick_Handler

VTABLE:
.long   Stack_start_c0
.long   Reset_Handler + 1 
.long   NMI_Handler
.long   HardFault_Handler
.long	MemManage_Handler
.long	BusFault_Handler
.long	UsageFault_Handler
.long	0
.long	0
.long	0
.long	0
.long	SVC_Handler + 1
.long	DebugMon_Handler
.long	0
.long	PendSV_Handler
.long	SysTick_Handler
.long	undefined_handler      
.long	undefined_handler      
.long	undefined_handler      
.long	undefined_handler      
.long	0                      
.long	undefined_handler      
.long	undefined_handler      
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.long	undefined_handler		
.size VTABLE, . - VTABLE


.section ".startup","ax"
.thumb
.set VTOR_REG,  0xE000ED08                 
.set MASTER_ID, 0x4001FC00                 
.set MAIN_CORE, 0x0
.align 2

.thumb 
.globl Reset_Handler
Reset_Handler:
.globl _start
_start:

BL ClearRegister

BL SetUpVtorRegister

BL SetStack

BL RamInit

BL InitData

BL ClearBss

_MAIN:
  CPSIE i  
  BL main
  
.globl ThoNVEnd
ThoNVEnd:
    CMP R1,#1

ClearRegister:
    MOV     R0,#0
    MOV     R1,#0
    MOV     R2,#0
    MOV     R3,#0
    MOV     R4,#0
    MOV     R5,#0
    MOV     R6,#0
    MOV     R7,#0
    MOV     PC, LR

SetUpVtorRegister:
    LDR     R0, =VTOR_REG
    LDR     R1, =VECTORTABLE_START
    STR     R1, [R0]
    MOV     PC, LR

SetStack:
    LDR     r0, =Stack_start_c0
    MSR     MSP, r0
    MOV     PC, LR

RamInit:
    LDR     R0, =RAM_INIT
    CMP     R0, #0
    BEQ     SRAM_End
    LDR     R1, =INT_SRAM_START
    LDR     R2, =INT_SRAM_END
    SUBS    R2, R1
    SUBS    R2, #1 
    BLE     SRAM_End 
    MOVS    R0, #0
    MOVS    R3, #0
SRAM_Loop:
    STM     R1!, {R0, R3} 
    SUBS    R2, #8
    BGE     SRAM_Loop 
SRAM_End:
    MOV     PC, LR

InitData:
    LDR     R0, =INIT_TABLE
    LDR     R6, =INIT_TABLE_END
    SUBS    R5, R6, R0 
    ADDS    R5, R5, #12
SetaddRegionData:
    SUBS    R5, R5, #12
    CMP     R5, #0
    BEQ     InitData_End 
    LDR     R1, [R0]
    LDR     R2, [R0, #4]
    LDR     R3, [R0, #8]
    ADDS    R0, R0, #12
    SUBS    R4, R3, R2
    CMP     R4, #0
    BEQ     SetaddRegionData 
CopyDataFlashtoRam:
    LDR     R4,[R2]
    STR     R4,[R1]
    ADDS    R1, R1, #1
    ADDS    R2, R2, #1
    CMP     R2, R3
    BEQ     SetaddRegionData 
    B       CopyDataFlashtoRam
InitData_End:
    MOV  PC, LR

ClearBss:
    LDR     R0, =ZERO_TABLE
    LDR     R6, =ZERO_TABLE_END
    SUBS    R5, R6, R0
    ADDS    R5, R5, #8
SetAddRegionBss:
    SUBS    R5, R5, #8
    CMP     R5, #0
    BEQ     ClearBss_End
    LDR     R1, [R0]
    LDR     R2, [R0, #4]
    ADDS    R0, R0, #8
    SUBS    R4, R2, R1
    CMP     R4, #0
    BEQ     SetAddRegionBss
EraseBss:
    MOVS    R4, #0
    STR     R4,[R1]
    ADDS    R1, R1, #1
    CMP     R2, R1
    BEQ     SetAddRegionBss
    B       EraseBss
ClearBss_End:
    MOV     PC, LR
    
.align 4
.ltorg
