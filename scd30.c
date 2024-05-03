#include "scd30.h"

#define SCD30_Address 0x61

//Clock stretching period in write- and read-frames is 30 ms, however, due to internal calibration
//processes a maximal clock stretching of 150 ms may occur once per day.

//The boot-up time is < 2 s.
struct SCD30 scd30_init() { // No repeated restart could happen
	HAL_Delay(2000);
}


void SCD30_Trigger_Continuous_Measurement(uint16_t pressure_compensation = 0) {
	uint8_t pData[6] = {0xC2, 0x00, 0x10, pressure_compensation>>8, pressure_compensation, 0x81};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_Address, pData, 6, 200);
}

void SCD30_Continuous_Measurement_Stop() {
	uint8_t pData[2] = {0x01, 0x04};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_Address, pData, 2, 200);
}

void SCD30_Set_Measurement_Interval(uint16_t interval) {
	uint8_t pData[6] = {0xC2, 0x46, 0x00, interval>>8, interval, 0xE3};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_Address, pData, 6, 200);
}

uint8_t SCD30_Get_Data_Ready_Status() {
	uint8_t pData[3] = {0xC2, 0x02, 0x02};
	HAL_I2C_Master_Transmit(&hi2c1, SCD30_Address, pData, 3, 200);

	HAL_Delay(3);
	uint8_t buffer[3] = {0, 0, 0};
	HAL_I2C_Master_Receive(&hi2c1, SCD30_Address, buffer, 2, 200);
	return buffer[1];
}

//

void SCD30_Get_Data (*SCD30_Data data) {

};
void SCD30_Toggle_ASC() {

}
