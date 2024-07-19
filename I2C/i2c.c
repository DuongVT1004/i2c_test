#include "i2c.h"
#include "main.h"
#include "string.h"

extern I2C_HandleTypeDef hi2c1;

#define SIZE 10
uint8_t rx_Data[SIZE];
//uint8_t tx_Data[SIZE];

uint8_t rxcount = 0;
uint8_t txcount = 0;
//uint8_t firstData = 0;

//char txData[] = "This is slave";

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	if(TransferDirection == I2C_DIRECTION_TRANSMIT)
	{
		// Master want to write data
//		if(firstData == 0)
//		{
			rxcount = 0;
			HAL_I2C_Slave_Seq_Receive_IT(&hi2c1, rx_Data, 1, I2C_FIRST_FRAME);
		//}
	}
	else
	{
		// Master want to read data
		Error_Handler();
	}
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (rxcount < SIZE)
		{
			if (rxcount == SIZE-1)
			{
				HAL_I2C_Slave_Sequential_Receive_IT(hi2c, rx_Data+rxcount, 1, I2C_LAST_FRAME);
			}
			else
			{
				HAL_I2C_Slave_Sequential_Receive_IT(hi2c, rx_Data+rxcount, 1, I2C_NEXT_FRAME);
			}
		}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_EnableListen_IT(&hi2c1);
}