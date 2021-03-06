/*
 * DHT.h
 *
 *  Created on: Jun 28, 2020
 *      Author: Controllerstech.com
 */

#ifndef DHT_H_
#define DHT_H_



uint8_t Reset_Pulse(void);
void send(uint8_t data);
uint8_t read(void);
void send_byte(char value);
unsigned char read_byte(void);
void gpio_set_input (void);
void gpio_set_output (void);

#endif /* INC_DHT_H_ */
