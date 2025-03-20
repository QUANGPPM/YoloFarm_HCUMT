#ifndef OUTPUT_MODULE_H__
#define OUTPUT_MODULE_H__
#include "Adruino_lib.h"

void output_setup();
void lcd_display(double temperature, int humidity, int lightSensorValue, int soilMoisturePercent);

extern LiquidCrystal_I2C lcd;

#endif