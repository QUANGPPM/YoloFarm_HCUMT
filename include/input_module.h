#ifndef INPUT_MODULE_H__
#define INPUT_MODULE_H__
#include "Adruino_lib.h"

void sensor_setup();

// get data:
void getDht20Data(double* temperature, double* humidity);
void getSmAndLuxData(int* soilMoisturePercent, int* lightSensorValue);

#endif