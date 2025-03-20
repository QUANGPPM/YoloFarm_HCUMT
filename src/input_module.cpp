#include "input_module.h"



/*              READ DHT20 SENSOR            */
DHT20 dht;
void dht20_setup(){
    // Khởi tạo cảm biến DHT20
    dht.begin();
    Serial.println("DHT20 sensor initialized.");
}

void getDht20Data(double* temperature, double* humidity){

    dht.read();
    *temperature = dht.getTemperature();
    *humidity = dht.getHumidity();
#if DEBUG == 2
    // Hiển thị kết quả lên Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(*temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(*humidity);
    Serial.println(" %");

#endif
}


/*              READ SOIL MOISTURE & LIGHT SENSOR            */
const int soilMoisturePin = P1_ADC; // Chân analog của cảm biến độ ẩm đất
const int lightSensorPin = P0_ADC;  // Chân analog của cảm biến ánh sáng
int soilMoistureRaw = 0;        //lưu giá trị thô từ cảm biến

void sm_and_lux_setup(){
    // nothing
}

void getSmAndLuxData(int* soilMoisturePercent, int* lightSensorValue){
    // Đọc giá trị từ cảm biến độ ẩm đất
    soilMoistureRaw = analogRead(soilMoisturePin); // Giá trị thô (0-4095)
    
    // Chuyển đổi giá trị độ ẩm đất sang thang 0-100%
    *soilMoisturePercent = map(soilMoistureRaw, 0, 4095, 0, 100);

    // Đọc giá trị từ cảm biến ánh sáng
    *lightSensorValue = analogRead(lightSensorPin); // Giá trị thô (0-4095)


#if DEBUG == 2
    // Hiển thị kết quả lên Serial Monitor
    Serial.print("Soil Moisture: ");
    Serial.print(*soilMoisturePercent);
    Serial.println("%");

    Serial.print("Light Sensor Value: ");
    Serial.println(*lightSensorValue); 
#endif  
}



/*              SETUP SENSOR            */
void sensor_setup(){
    // Khởi tạo cảm biến DHT20
    dht20_setup();
    // Khởi tạo cảm biến đo độ ẩm đất và ánh sáng
    sm_and_lux_setup();
}