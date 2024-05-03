
#ifndef INC_SCD30_H_
#define INC_SCD30_H_

#include "i2c.h"

struct SCD30_Data {
	float co2Concentration;
	float temperature;
	float rHumidity;
};

struct SCD30 {
	uint8_t channel;
	SCD30_Data data;
};

// below are functions definitions of struct
struct SCD30 scd30_init(uint8_t ch);
float SCD30_Get_Temperature(struct SCD30* scd);
float SCD30_Get_rHumidity(struct SCD30* scd);
float SCD30_Get_CO2(struct SCD30* scd);
void  SCD30_Set_Data(); // refresh

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

// below is the function definition for mux control
void XXX_Set_Channel(uint8_t ch);

#endif /* INC_SCD30_H_ */
