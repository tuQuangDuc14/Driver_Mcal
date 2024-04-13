#ifndef SYSTEM_H
#define SYSTEM_H

void NMI_Handler(void)                  __attribute__ ((weak));
void HardFault_Handler(void)            __attribute__ ((weak));
void MemManage_Handler(void)            __attribute__ ((weak));
void BusFault_Handler(void)             __attribute__ ((weak));
void UsageFault_Handler(void)           __attribute__ ((weak));
void DebugMon_Handler(void)             __attribute__ ((weak));
void PendSV_Handler(void)               __attribute__ ((weak));
void SysTick_Handler(void)              __attribute__ ((weak));
void undefined_handler(void);

#endif 
