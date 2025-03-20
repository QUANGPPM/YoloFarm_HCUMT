#ifndef CONNECTION_H__
#define CONNECTION_H__
#include "Adruino_lib.h"
//-------------------------------------------------------------------------//
#define WIFI_NAME "ACLAB"
#define PASSWORD "ACLAB2023"

//-------------------------------------------------------------------------//
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883 // Cổng MQTT
#define AIO_USERNAME    "quangppm"
#define AIO_KEY         "password <write>"
//-------------------------------------------------------------------------//
//Publisher
#define TEMPERATURE_FEED_ID     "/feeds/yolofarm.farm-temperature"
#define HUMIDITY_FEED_ID        "/feeds/yolofarm.farm-humidity"
#define LIGHT_FEED_ID           "/feeds/yolofarm.farm-light-intensity"
#define SOIL_MOISTURE_FEED_ID   "/feeds/yolofarm.farm-soil-moisture"
#define GDD_FEED_ID             "/feeds/yolofarm.farm-gdd"
//Subscriber
#define STATUS_FEED_ID          "/feeds/yolofarm.farm-status"
#define PUMP_1_FEED_ID          "/feeds/yolofarm.farm-pump-1"
#define PUMP_2_FEED_ID          "/feeds/yolofarm.farm-pump-2"


//-------------------------------------------------------------------------//
// Wifi connection:
bool wifiConnected();

// Adafruit function:
void MQTT_connect(); // duy trì kết nối -> loop
void feedsSubscribe(); // đăng kí nhận dữ liệu từ feed
void sendData(double temperature, double humidity, double light, double soilMoisture, int GDD);
void receiveData();
// feed variable:
extern Adafruit_MQTT_Client mqtt;

// Send and receive data:
// Tạo publisher: Nhiệt độ - độ ẩm, độ ẩm đất, ánh sáng, GDD
extern Adafruit_MQTT_Publish temperatureFeed;
extern Adafruit_MQTT_Publish humidityFeed;
extern Adafruit_MQTT_Publish lightFeed;
extern Adafruit_MQTT_Publish soilMoistureFeed;
extern Adafruit_MQTT_Publish GDDFeed;
// Tạo subscriber: Tình trạng, Máy Bơm 1, Máy Bơm 2, GDD
extern Adafruit_MQTT_Subscribe statusFeed;
extern Adafruit_MQTT_Subscribe pump1Feed;
extern Adafruit_MQTT_Subscribe pump2Feed;
extern Adafruit_MQTT_Subscribe getGDDFeed;
#endif