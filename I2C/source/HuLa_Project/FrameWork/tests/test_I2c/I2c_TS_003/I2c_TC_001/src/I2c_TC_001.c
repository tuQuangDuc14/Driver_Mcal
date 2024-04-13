#include <string.h>
#include "Header.h"
#include "I2c_TC_001.h"
#include "I2c_TS_003.h"
#include "HuLa_Gpio_IP.h"
#include "HuLa_I2c_IP.h"
#include "HuLa_Mcu_IP.h"

#define MY_ADDR 0x61;
#define SLAVE_ADDR  0x68
uint8_t Msg[14] = "Hello ThoNV12\n";
uint8_t i=0;

I2C_Handle_t I2C1Handle;

uint8_t rcv_buf[32];
uint8_t Data_receive_1;
uint8_t a =0;
uint8_t b =0;

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
  I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
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

	  I2C1_GPIOInits();
	  I2C1_Inits();
	  I2C_PeripheralControl(I2C1,ENABLE);

	  I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV,ENABLE);
	  I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER,ENABLE);

    for(uint32_t i = 0 ; i < 500000/2 ; i ++); // delay

    //Receive 1 bit
    uint8_t data = 0x01;
    while(I2C_MasterSendDataIT(&I2C1Handle,&data,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY);
    while(I2C_MasterReceiveDataIT(&I2C1Handle,&Data_receive_1,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY);
    for(uint32_t i = 0 ; i < 500000/2 ; i ++){}

    RESULT_Assert(Data_receive_1 == 20 );

    //Receive bit > 1
    data = 0x02;
    while(I2C_MasterSendDataIT(&I2C1Handle,&data,1,SLAVE_ADDR,I2C_ENABLE_SR)!= I2C_READY);
    while(I2C_MasterReceiveDataIT(&I2C1Handle,rcv_buf,14,SLAVE_ADDR,I2C_DISABLE_SR) != I2C_READY);

    for(uint32_t i = 0 ; i < 500000/2 ; i ++){}

    for(i=0;i<14;i++)
    {
      RESULT_Assert(rcv_buf[i]==Msg[i]);
    }
}

void I2C1_EV_IRQHandler (void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler (void)
{
	I2C_ER_IRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv)
{
     if(AppEv == I2C_EV_TX_CMPLT)
     {
    	  a =1;
     }else if (AppEv == I2C_EV_RX_CMPLT)
     {
    	  b=1;
     }
     else if (AppEv == I2C_ERROR_AF)
     {
      // exam SLAVE_ADDR  0x69 kkk
    	  I2C_CloseSendData(pI2CHandle);
        I2C_GenerateStopCondition(I2C1);
        while(1);
     }
}