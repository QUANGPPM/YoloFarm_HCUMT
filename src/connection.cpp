#include "connection.h"

//======================== WIFI ==============================//
const char* ssid = WIFI_NAME;       // Tên mạng WiFi
const char* password = PASSWORD; // Mật khẩu WiFi

bool wifiConnected(){
    Serial.println("Đang kết nối WiFi...");
    // Kết nối WiFi
    WiFi.begin(ssid, password);
    
    int timeout = 30; // Chờ tối đa 30 lần (15 giây)
    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        delay(500);
        Serial.print(".");
        timeout--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nKết nối WiFi thành công!");
        Serial.print("Địa chỉ IP: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nKhông kết nối được, kiểm tra lại WiFi.");
        return false;
    }
}

//======================== SERVER ==============================//
// Kết nối Wi-Fi
WiFiClient client;

// Tạo MQTT client
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Tạo publisher: Nhiệt độ - độ ẩm, độ ẩm đất, ánh sáng, GDD
Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME TEMPERATURE_FEED_ID);
Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME HUMIDITY_FEED_ID);
Adafruit_MQTT_Publish lightFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME LIGHT_FEED_ID);
Adafruit_MQTT_Publish soilMoistureFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME SOIL_MOISTURE_FEED_ID);
Adafruit_MQTT_Publish GDDFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME GDD_FEED_ID);

// Tạo subscriber: Tình trạng, Máy Bơm 1, Máy Bơm 2
Adafruit_MQTT_Subscribe statusFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME STATUS_FEED_ID);
Adafruit_MQTT_Subscribe pump1Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME PUMP_1_FEED_ID);
Adafruit_MQTT_Subscribe pump2Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME PUMP_2_FEED_ID);
Adafruit_MQTT_Subscribe getGDDFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME GDD_FEED_ID);
// Duy trì kết nối
void MQTT_connect() {
    int8_t ret;

    if (mqtt.connected()) {
        return; // Đã kết nối
    }

    Serial.print("Connecting to MQTT...");
    while ((ret = mqtt.connect()) != 0) { 
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying in 5 seconds...");
        mqtt.disconnect();
        delay(5000);  
    }
    Serial.println("MQTT Connected!");
}

/*Đăng kí nhận dữ liệu từ feed:*/ 
void feedsSubscribe(){
    mqtt.subscribe(&statusFeed);
    mqtt.subscribe(&pump1Feed);
    mqtt.subscribe(&pump2Feed);
    mqtt.subscribe(&getGDDFeed);
}
/*Nhận dữ liệu từ feed:*/ 

unsigned long lastCheck = 0;
const unsigned long checkInterval = 100; // Kiểm tra mỗi 100ms
Adafruit_MQTT_Subscribe *subscription;
void receiveData(){
    // Kiểm tra định kỳ thay vì chờ lâu
    if (millis() - lastCheck >= checkInterval) {
        lastCheck = millis();

        // Kiểm tra xem có dữ liệu mới từ MQTT không
        Adafruit_MQTT_Subscribe *subscription = mqtt.readSubscription(0); // Không chờ
        if (subscription) {
            if (subscription == &pump1Feed) {
                Serial.print("Received LED Feed Value: ");
                Serial.println((char *)pump1Feed.lastread); // Hiển thị giá trị nhận được từ feed LED
            }
        }
    }
}

/*Gửi dữ liệu lên feed:*/ 
void sendData(double temperature, double humidity, double light, double soilMoisture, int GDD){

    static int sended = 0;
    switch(sended){
        case 0:
            sended = 1;
            temperatureFeed.publish(temperature);
            break;
        case 1:
            sended = 2;
            humidityFeed.publish(humidity);
            break;
        case 2:
            sended = 3;
            lightFeed.publish(light);
            break;
        case 3:
            sended = 4;
            soilMoistureFeed.publish(soilMoisture);
            break;
        case 4:
            sended = 0;
            GDDFeed.publish(GDD);
            break;

    }
}
