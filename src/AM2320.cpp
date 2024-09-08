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

#include "AM2320.h"

/* --- constuctor --- */
AM2320::AM2320() {
	Wire.begin();
}

/* --- status --- */
uint8_t AM2320::status() {
	return read(NULL, NULL);
}


/* --- main read function --- */
uint8_t AM2320::read(float* temp, float* hum) {
	uint8_t buffer_read[AM2320_BUFFER_READ];
	uint16_t CRC_read = 0;
	uint16_t temp_read = 0;
	uint16_t hum_read = 0;

	Wire.beginTransmission(AM2320_DEVICE_ADDRESS);
	Wire.endTransmission(false);
	delayMicroseconds(1000);
	Wire.endTransmission(true);

	Wire.beginTransmission(AM2320_DEVICE_ADDRESS);
	Wire.write(AM2320_READ_DATA_CODE);
	Wire.write((uint8_t) 0x00);
	Wire.write((uint8_t) 0x04);

	if (Wire.endTransmission()) {
		return 1;
	}
	delay(2);

	Wire.requestFrom(AM2320_DEVICE_ADDRESS, AM2320_BUFFER_READ);
	if (Wire.available() != AM2320_BUFFER_READ) {
		return 2;
	}

	for (char i = 0;i < AM2320_BUFFER_READ;i++) {
		buffer_read[i] = Wire.read();
	}
	if (buffer_read[0] != AM2320_READ_DATA_CODE) {
		return 3;
	}

	if (temp != NULL && hum != NULL) {
		CRC_read = buffer_read[7] << 8;
		CRC_read |= buffer_read[6];
		if (CRC_read != CRC16(buffer_read, 6)) {
			return 4;
		}
	}

	if (temp != NULL) {
		temp_read = ((uint16_t)(buffer_read[4] & 0x7F) << 8) | buffer_read[5];
		*temp = temp_read / 10.0;
		*temp *= (buffer_read[4] & 0x80) ? (-1) : 1;
	}
	if (hum != NULL) {
		hum_read = ((uint16_t)buffer_read[2] << 8) | buffer_read[3];
		*hum = hum_read / 10.0;
	}

	return 0;
}

/* --- read temperature function --- */
float AM2320::getT() {
	float temp_read = 0;

	read(&temp_read, NULL);
		
	return temp_read;
}

/* --- read humidity function --- */
float AM2320::getH() {
	float hum_read = 0;

	read(NULL, &hum_read);
	
	return hum_read;
}


/* --- check function --- */
uint16_t AM2320::CRC16(uint8_t* ptr, uint8_t len) {
	uint16_t crc = 0xFFFF;
	uint8_t i = 0x00;

	while (len--) {
		crc ^= *ptr++;
		for (i = 0; i < 8; i++) {
			if (crc & 0x01) {
				crc >>= 1;
				crc ^= 0xA001;
			}
			else crc >>= 1;
		}
	}
	return crc;
}