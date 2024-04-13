#ifdef __cplusplus
extern "C"{
#endif

#include "system_hula.h"

void NMI_Handler(void)
{
    while(1){};
}

void HardFault_Handler(void)
{
    while(1){};
}


void MemManage_Handler(void)
{
    while(1){};
}


void BusFault_Handler(void)
{
    while(1){};
}


void UsageFault_Handler(void)
{
    while(1){};
}

void DebugMon_Handler(void)
{
    while(1){};
}


void PendSV_Handler(void)
{
    while(1){};
}


void SysTick_Handler(void)
{
    while(1){};
}


void undefined_handler(void)
{
   while(1){};
}

void SVC_Handler(void)  __attribute__ ((weak));
void SVC_Handler(void)
{
    while(1){};
}

#ifdef __cplusplus
}
#endif
