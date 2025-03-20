//library for iot
#include "Adruino_lib.h"
#include "connection.h"
#include "input_module.h"
#include "output_module.h"

#define READ_SENSOR_TIME 2000
#define SEND_DATA_TIME 3000
/* DEBUG:
 *   
*/
/** DEBUG
 * 0 - khong lam gi
 * 1 - test ket noi wifi, server
 * 2- test doc tin hieu ngoai vi
 */

/* Declare variable */
double temperature = 0;
double humidity = 0;
int soilMoisturePercent = 0;
int lightSensorValue = 0;
int GDD = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();         // Khởi tạo giao thức I2C
  Serial.println("ESP32 đang khởi động...");
  delay(1000);
  sensor_setup();
  output_setup();

#if DEBUG == 1 || DEBUG == 0
  // kết nối wifi
  if(wifiConnected()){
    // đăng kí nhận dữ liệu
    feedsSubscribe();
    MQTT_connect();
  }        
  else{
    while(true);
  }
#endif



}

void loop() {
  static unsigned long readDelayTime;
  static unsigned long sendDataTime;
  static unsigned long caculateGDDTime;
/**************************************************************************/
receiveData();

/**************************************************************************/
  // Read Sensor
  if(millis() - readDelayTime >= READ_SENSOR_TIME){
    
    //get data:
    getDht20Data(&temperature, &humidity);
    getSmAndLuxData(&soilMoisturePercent, &lightSensorValue);

    // //print serial:
    // Serial.print("Soil Moisture: ");
    // Serial.print(soilMoisturePercent);
    // Serial.println("%");
    // Serial.print("Light Sensor Value: ");
    // Serial.println(lightSensorValue); 
    // Serial.print("Temperature: ");
    // Serial.print(temperature);
    // Serial.println(" °C");
    // Serial.print("Humidity: ");
    // Serial.print(humidity);
    // Serial.println(" %");

    //display LCD creen:
    lcd_display(temperature, humidity, lightSensorValue, soilMoisturePercent);
    
    readDelayTime = millis();
  }
/**************************************************************************/
  //caculate:
  if(millis() - caculateGDDTime >= 1000){

    if(lightSensorValue >= 2000)
      GDD++;
    caculateGDDTime = millis();

  }
/**************************************************************************/
  if(millis() - sendDataTime >= SEND_DATA_TIME){
#if DEBUG == 1 || DEBUG == 0
    MQTT_connect();
#endif
    //send data to Feed:
    sendData(temperature, humidity, lightSensorValue, soilMoisturePercent, GDD);
    sendDataTime = millis();
  }

}

