/*
 * Library: AM2320
 *
 * Description: Short library that reads temperature and humidity.
 * 
 * Author: Vereshchynskyi Nazar
 * Email: verechnazar12@gmail.com
 * Version: 1.0.0
 * Date: 08.04.2024
 */

#ifndef _AM2320_H
#define _AM2320_H

#include <Arduino.h>
#include <Wire.h>

/* --- device address & system definitions --- */
#define AM2320_DEVICE_ADDRESS (0xB8 >> 1)
#define AM2320_READ_DATA_CODE 0x03
#define AM2320_BUFFER_READ 8

/* --- main class --- */
class AM2320 {
public:
	AM2320();
	uint8_t status();

	uint8_t read(float*, float*);
	float getT();
	float getH();

private:
	uint16_t CRC16(uint8_t*, uint8_t);
};

#endif