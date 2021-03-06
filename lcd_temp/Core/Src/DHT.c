

/************** MAKE CHANGES HERE ********************/
#include "stm32f4xx_hal.h"

#define TYPE_DHT11    // define according to your sensor
//#define TYPE_DHT22

GPIO_InitTypeDef GPIO_InitStruct;
#define PORT GPIOA
#define PIN GPIO_PIN_1




/*******************************************     NO CHANGES AFTER THIS LINE      ****************************************************/

#include "DHT.h"


uint8_t Reset_Pulse(void)
{

	gpio_set_output ();
	HAL_GPIO_WritePin(PORT, PIN ,0);
	HAL_Delay(0.480);

	gpio_set_input ();
	HAL_Delay(0.080);


	if(!(HAL_GPIO_ReadPin(PORT, PIN))){
		HAL_Delay(0.400);
		return 0;
	}
	else
	{
		HAL_Delay(0.400);
		return 1;
	}



}



void send(uint8_t data)
{
	gpio_set_output ();  // set as output
	for (int i=0; i<8; i++)
	{
		if ((data & (1<<i))!=0)  // LSB first
		{
			// write 1 sequence

			gpio_set_output ();  // set as output
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, 0); // Pull the Pin LOW
			HAL_Delay(0.001);  // wait for 1us
			gpio_set_input (); // set the pin as input
			HAL_Delay(0.060);  // wait for 60us
		}

		else
		{
			// write 0
			gpio_set_output ();
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, 0);
			HAL_Delay(0.060);
			gpio_set_input ();
		}
	}
}
uint8_t  read(void)
{
		uint8_t value=0;
		gpio_set_input ();  // set the pin as input

		for (int i=0;i<8;i++)
		{
	              // Initiate READ

			gpio_set_output ();  // set as output
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1,0);  // pull the pin LOW
			HAL_Delay(0.002); // wait for 2 us

			gpio_set_input ();  // set as input
			if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1))  // if the pin is high
			{
				value |= 1<<i;  // write 1
			}
			HAL_Delay(0.060);  // wait for 60 us

		}
		return value;

}
void send_byte(char value)
{
	unsigned char i;
	unsigned char pom;

	for(i=0; i<8; i++)
	{
		pom = value >> i;
		pom &= 0x01;
		send(pom);
	}
	HAL_Delay(0.100);
}

unsigned char read_byte(void)
{
	unsigned char i;
	unsigned char value=0;

	for(i=0; i<8; i++)
	{
		if(read())
		{
			value |= 0x01 << i;
		}

		HAL_Delay(0.015);
	}
	return(value);


}

void gpio_set_input (void)
{
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void gpio_set_output (void)
{
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}






