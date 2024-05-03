#include "scd30.h"

#define SCD30_ADDRESS 0x61
#define XXXXX_ADDRESS 0x70

//Clock stretching period in write- and read-frames is 30 ms, however, due to internal calibration
//processes a maximal clock stretching of 150 ms may occur once per day.

//The boot-up time is < 2 s.
struct SCD30 scd30_init(uint8_t ch) { // No repeated restart could happen
	struct SCD30 scd30;
	scd30.channel = ch;

	HAL_Delay(2000);
	return scd30;
}

float SCD30_Get_Temperature(struct SCD30* scd) {
	return scd->data.temperature;
}

float SCD30_Get_rHumidity(struct SCD30* scd) {
	return scd->data.rHumidity;
}

float SCD30_Get_CO2(struct SCD30* scd) {
	return scd->data.co2Concentration;
}

void SCD30_Trigger_Continuous_Measurement(uint16_t pressure_compensation = 0) {
	uint8_t pData[6] = {0xC2, 0x00, 0x10, pressure_compensation>>8, pressure_compensation, 0x81};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_ADDRESS, pData, 6, 200);
}

void SCD30_Continuous_Measurement_Stop() {
	uint8_t pData[2] = {0x01, 0x04};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_ADDRESS, pData, 2, 200);
}

void SCD30_Set_Measurement_Interval(uint16_t interval) {
	uint8_t pData[6] = {0xC2, 0x46, 0x00, interval>>8, interval, 0xE3};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_ADDRESS, pData, 6, 200);
}

uint8_t SCD30_Get_Data_Ready_Status() {
	uint8_t pData[3] = {0xC2, 0x02, 0x02};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_ADDRESS, pData, 3, 200);

	HAL_Delay(3);
	uint8_t buffer[3] = {0, 0, 0};
	HAL_I2C_Master_Receive(&hi2c1, SCD30_ADDRESS, buffer, 2, 200);
	return buffer[1];
}

//

void SCD30_Get_Data (struct SCD30_Data * data) {

	while (SCD30_Get_Data_Ready_Status() != 1)
	{
		HAL_Delay(2000);
	}

	uint8_t pData[3] = {0xC2, 0x03, 0x00};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_ADDRESS, pData, 3, 200);

	HAL_Delay(3);
	uint8_t buffer[19] = {0xC3};
	HAL_I2C_Master_Receive(&hi2c1, SCD30_ADDRESS, buffer, 19, 200);

	//CO2 values
	unsigned int tempU32;
	// read data is in a buffer. In case of I2C CRCs have been removed
	// beforehand. Content of the buffer is the following
	unsigned char temp_buffer[4];
	temp_buffer[0] = buffer[1]; //  MMSB CO2
	temp_buffer[1] = buffer[2]; //  MLSB CO2
	temp_buffer[2] = buffer[4]; //  LMSB CO2
	temp_buffer[3] = buffer[5]; //  LLSB CO2
	// cast 4 bytes to one unsigned 32 bit integer
	tempU32 = (unsigned int)((((unsigned int)buffer[0]) << 24) |
	(((unsigned int)buffer[1]) << 16) |
	(((unsigned int)buffer[2]) << 8)  |
	((unsigned int)buffer[3]));
	// cast unsigned 32 bit integer to 32 bit float
	data->co2Concentration = *(float*)&tempU32;

	//Temperature values
	temp_buffer[0] = buffer[7]; //  MMSB Temperature
	temp_buffer[1] = buffer[8]; //  MLSB Temperature
	temp_buffer[2] = buffer[10]; //  LMSB Temperature
	temp_buffer[3] = buffer[11]; //  LLSB Temperature
	// cast 4 bytes to one unsigned 32 bit integer
	tempU32 = (unsigned int)((((unsigned int)buffer[0]) << 24) |
	(((unsigned int)buffer[1]) << 16) |
	(((unsigned int)buffer[2]) << 8)  |
	((unsigned int)buffer[3]));
	// cast unsigned 32 bit integer to 32 bit float
	data->temperature = *(float*)&tempU32;

	//Humidity values
	temp_buffer[0] = buffer[13]; //  MMSB Humidity
	temp_buffer[1] = buffer[14]; //  MLSB Humidity
	temp_buffer[2] = buffer[16]; //  LMSB Humidity
	temp_buffer[3] = buffer[17]; //  LLSB Humidity
	// cast 4 bytes to one unsigned 32 bit integer
	tempU32 = (unsigned int)((((unsigned int)buffer[0]) << 24) |
	(((unsigned int)buffer[1]) << 16) |
	(((unsigned int)buffer[2]) << 8)  |
	((unsigned int)buffer[3]));
	// cast unsigned 32 bit integer to 32 bit float
	data->rHumidity = *(float*)&tempU32;


}

void SCD30_Toggle_ASC() { //1.4.6 (De-)Activate Automatic Self-Calibration (ASC)

}

void SCD30_Set_FRC() { //Set Forced Recalibration value (FRC)

}

void SCD30_Set_Temp_Offset() {

}

void SCD30_Set_Altitude_Compensation() {

}

void SCD30_Get_Firmware_Version() {

}

void XXX_Set_Channel(uint8_t ch) {
	HAL_I2C_Master_Transmit(&hi2c1, XXXXX_ADDRESS, 1<<ch, 1, 100);
}
