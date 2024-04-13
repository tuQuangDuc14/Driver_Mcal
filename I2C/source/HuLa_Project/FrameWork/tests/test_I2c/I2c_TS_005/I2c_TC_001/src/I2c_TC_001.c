#include <string.h>
#include "Header.h"
#include "I2c_TC_001.h"
#include "I2c_TS_005.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_I2c_IP.h"
#include "HuLa_Mcu_IP.h"

#define MY_ADDR 0x68;
 uint32_t data_len=0;
#define SLAVE_ADDR  0x68
uint8_t check=1;

 //very large message
uint8_t Tx_buf[] = "HiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHi...123";

uint8_t CommandCode;

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

I2C_Handle_t I2C1Handle;

//rcv buffer
uint8_t rcv_buf[32];

/*
 * PB6-> SCL
 * PB7 -> SDA
 */

void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	//scl
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);
	//sda
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&I2CPins);
}

void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}


void I2c_TC_001(void)
{
	data_len = 200;
	I2C1_GPIOInits();
	I2C1_Inits();
	I2C_PeripheralControl(I2C1,ENABLE);
	//ack bit is made 1 after PE=1
	I2C_ManageAcking(I2C1,I2C_ACK_ENABLE);

	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER,ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV,ENABLE);

	I2C_SlaveEnableDisableCallbackEvents(I2C1,ENABLE);
	
	while(check);
	RESULT_Assert(1);
}
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv)
{
	static uint32_t cnt = 0;
	static uint32_t w_ptr = 0;
	if(AppEv == I2C_ERROR_AF)
	{
		//This will happen during slave transmitting data to master .
		// slave should understand master needs no more data
		//slave concludes end of Tx
		//if the current active code is 0x02 then dont invalidate
		if(! (CommandCode == 0x02))
			CommandCode = 0XFF;
		//reset the cnt variable because its end of transmission
		cnt = 0;

		//Slave concludes it sent all the bytes when w_ptr reaches data_len
		if(w_ptr >= (data_len))
		{
			w_ptr=0;
			CommandCode = 0xff;
			check=0;
		}
	}else if (AppEv == I2C_EV_STOP)
	{
		//This will happen during end slave reception
		//slave concludes end of Rx
		cnt = 0;
	}else if (AppEv == I2C_EV_DATA_REQ)
	{
		//Master is requesting for the data . send data
		if(CommandCode == 0x01)
		{
			//Here i are sending 4 bytes of length information
			I2C_SlaveSendData(I2C1,((data_len >> ((cnt%4) * 8)) & 0xFF));
		    cnt++;
		}else if (CommandCode == 0x02)
		{
			I2C_SlaveSendData(I2C1,Tx_buf[w_ptr++]);
		}
	}else if (AppEv == I2C_EV_DATA_RCV)
	{
		 CommandCode = I2C_SlaveReceiveData(I2C1);
	}
}

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void)
{
	I2C_ER_IRQHandling(&I2C1Handle);
}