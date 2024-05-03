
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

#endif /* INC_SCD30_H_ */
