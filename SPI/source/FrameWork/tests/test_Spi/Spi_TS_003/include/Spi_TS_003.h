#ifndef Spi_TS_003_H
#define Spi_TS_003_H

#include "Spi_TC_001.h"
#include <stdint.h>

typedef void (* RESULT_TestCase_t)(void); 

typedef struct {
 uint8_t              TC_Count;
 RESULT_TestCase_t*   TC_Ptr;
} RESULT_TestSuite_t; 

void RESULT_RunAllTests(RESULT_TestSuite_t* TS);
void RESULT_Assert(uint8_t result);

#endif 