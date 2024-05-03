
#ifndef INC_SCD30_H_
#define INC_SCD30_H_

#include "i2c.h"

struct SCD30_Data {
	float co2Concentration;
	float temperature;
	float rHumidity;
};

struct SCD30 {
	SCD30_Data data;
};

struct SCD30 scd30_init();
float SCD30_Get_Temperature(struct SCD30* scd);
float SCD30_Get_rHumidity(struct SCD30* scd);
float SCD30_Get_CO2(struct SCD30* scd);

// below are function definitions for direct sensor control
void SCD30_Trigger_Continuous_Measurement(uint16_t pressure_compensation = 0);
void SCD30_Continuous_Measurement_Stop();
void SCD30_Set_Measurement_Interval(uint16_t interval);
uint8_t SCD30_Get_Data_Ready_Status();
void SCD30_Get_Data (struct SCD30_Data * data);
void SCD30_Toggle_ASC();
void SCD30_Set_FRC();
void SCD30_Set_Temp_Offset();
void SCD30_Set_Altitude_Compensation();
void SCD30_Get_Firmware_Version();


#endif /* INC_SCD30_H_ */
