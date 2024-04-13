#include <string.h>
#include "Header.h"
#include "I2c_TS_001.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_I2c_IP.h"
#include "HuLa_Mcu_IP.h"

#define MY_ADDR1 0x61;
#define SLAVE_ADDR1  0x68

I2C_Handle_t I2C1Handle1;

uint8_t rcv_buf1[32];
uint8_t Data_receive_1;

uint8_t Msg[14] = "Hello ThoNV12\n";
uint32_t i=0;

/*
 * PB6-> SCL
 * PB7 -> SDA
 */

void I2C1_GPIOInits1(void)
{
  GPIO_Handle_t I2CPins1;

  I2CPins1.pGPIOx = GPIOB;
  I2CPins1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
  I2CPins1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
  I2CPins1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
  I2CPins1.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
  I2CPins1. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  //scl
  I2CPins1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
  GPIO_Init(&I2CPins1);
  //sda
  I2CPins1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
  GPIO_Init(&I2CPins1);
}
void I2C1_Inits1(void)
{
  I2C1Handle1.pI2Cx = I2C1;
  I2C1Handle1.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
  I2C1Handle1.I2C_Config.I2C_DeviceAddress = MY_ADDR1;
  I2C1Handle1.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
  I2C1Handle1.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
  I2C_Init(&I2C1Handle1);
}

void I2c_TC_001(void)
{

	I2C1_GPIOInits1();
	I2C1_Inits1();
	I2C_PeripheralControl(I2C1,ENABLE);
	
  //Receive 1 bit
    uint8_t data1 = 0x01;
    I2C_MasterSendData(&I2C1Handle1,&data1,1,SLAVE_ADDR1,I2C_ENABLE_SR);
    I2C_MasterReceiveData(&I2C1Handle1,&Data_receive_1,1,SLAVE_ADDR1,I2C_ENABLE_SR);
    RESULT_Assert(Data_receive_1 == 20);

    for(i = 0 ; i < 500000/2 ; i ++); // delay

  //Receive bit > 1
    data1 = 0x02;
    I2C_MasterSendData(&I2C1Handle1,&data1,1,SLAVE_ADDR1,I2C_ENABLE_SR);
    I2C_MasterReceiveData(&I2C1Handle1,rcv_buf1,14,SLAVE_ADDR1,I2C_ENABLE_SR);

    for(i=0;i<14;i++)
    {
      RESULT_Assert(rcv_buf1[i]==Msg[i]);
    }
	  
}

