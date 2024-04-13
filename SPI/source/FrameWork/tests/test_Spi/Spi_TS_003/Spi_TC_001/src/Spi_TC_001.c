#include <string.h>
#include "Header.h"
#include "Spi_TC_001.h"
#include "Spi_TS_003.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_Spi_IP.h"


/*
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 -> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode : 5
 */
void SPI2_GPIOInits2(void)
{
	GPIO_Handle_t SPIPins2;
	SPIPins2.pGPIOx = GPIOB;
	SPIPins2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins2.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins2);

	//MOSI
	SPIPins2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins2);

	//MISO
	SPIPins2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins2);

	//NSS
	SPIPins2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins2);
}
void SPI2_Inits2(void)
{
	SPI_Handle_t SPI2handle2;
	SPI2handle2.pSPIx = SPI2;
	SPI2handle2.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle2.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle2.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;//generates sclk of 2MHz
	SPI2handle2.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle2.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle2.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle2.SPIConfig.SPI_SSM = SPI_SSM_DI;
	 //software slave management enabled for NSS pin
	SPI_Init(&SPI2handle2);
}

uint8_t Rececive_data1;

void Spi_TC_001(void)
{
	char data[] = "Hello ThoNV";
	uint8_t dataLen = 12;
	SPI2_GPIOInits2();
	SPI2_Inits2();
	/* SSM=0 ; SSOE=1 (NSS output enable);  */
	/* NSS sẽ được tự động quản lý bởi Hardware  */
	/* Khi SPE=1 ( Peripheral enabled) --> NSS=LOW, SPE=0  --> NSS=HIGH */
	SPI_SSOEConfig(SPI2,ENABLE);

	//enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	SPI_SendData(SPI2,&dataLen,1);

	SPI_SendData(SPI2,(uint8_t*)data,12);

	SPI_ReceiveData(SPI2,&Rececive_data1,1);

	//lets confirm SPI is not busy
	while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));

	//Disable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,DISABLE);
	
	RESULT_Assert(Rececive_data1 == 100);

}

