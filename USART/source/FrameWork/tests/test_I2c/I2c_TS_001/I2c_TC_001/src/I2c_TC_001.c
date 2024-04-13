#include <string.h>
#include "Header.h"
#include "I2c_TC_001.h"
#include "I2c_TS_001.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_I2c_IP.h"
#include "HuLa_Mcu_IP.h"

#define MY_ADDR 0x61;
#define SLAVE_ADDR  0x68

I2C_Handle_t I2C1Handle;
/*
 * PB6-> SCL
 * PB7 -> SDA
 */
uint8_t data[] = "Hello ThoNV12\n";
uint32_t i=0;
void I2C1_GPIOInits(void)
{
  GPIO_Handle_t I2CPins;
  /*Internal pull-up resistors are used */
  I2CPins.pGPIOx = GPIOB;
  I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
  I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
  /*
   *if you want to use external pullup resistors, then you have to use 3.3K pull up resistors
   * for both SDA and SCL lines
   */
  I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
  I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
  I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  //scl
  I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
  GPIO_Init(&I2CPins);
  //sda
  // PB7
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

	I2C1_GPIOInits();
	I2C1_Inits();
	I2C_PeripheralControl(I2C1,ENABLE);

    //send some data to the slave
    I2C_MasterSendData(&I2C1Handle,data,13,SLAVE_ADDR,0);

    for(i=0;i<=5000000;i++);
	
	RESULT_Assert(1);
}

