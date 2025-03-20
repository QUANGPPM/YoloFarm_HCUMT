#include "output_module.h"


/*              DISPLAY on LCD screen            */
// Khởi tạo màn hình LCD I2C với địa chỉ 0x27 và kích thước 16x2
LiquidCrystal_I2C lcd(0x21, 16, 2);

void lcd_setup(){
  // Khởi tạo LCD
  lcd.begin(16, 2);
  lcd.backlight();
}

void lcd_display(double temperature, int humidity, int lightSensorValue, int soilMoisturePercent){
    // Hiển thị thông tin lên màn hình LCD
    lcd.clear();
    
    // Dòng đầu tiên: RT và RH
    lcd.setCursor(0, 0);
    lcd.print("RT:");
    lcd.print(temperature, 1); // Hiển thị nhiệt độ với một chữ số thập phân
    lcd.print((char)223);      // Ký tự độ (°)
    lcd.print("C ");
    
    lcd.setCursor(10, 0);
    lcd.print("RH:");
    lcd.print(humidity);    // Hiển thị độ ẩm không khí với một chữ số thập phân
    lcd.print("%");

    // Dòng thứ hai: LUX và SM
    lcd.setCursor(0, 1);
    lcd.print("LUX:");
    lcd.print(lightSensorValue); // Hiển thị giá trị ánh sáng

    lcd.setCursor(10, 1);
    lcd.print("SM:");
    lcd.print(soilMoisturePercent); // Hiển thị độ ẩm đất theo %
    lcd.print("%");
}



/*              ADJUST RGB LED           */




void output_setup(){
    lcd_setup();
}