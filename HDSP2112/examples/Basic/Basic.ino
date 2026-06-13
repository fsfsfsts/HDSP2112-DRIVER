#include <HDSP2112.h>

HDSP2112 lcd;

void setup() {
  lcd.begin();
}

void loop() {
  // 显示数字
  lcd.write(lcd.num[1], 0);  // 1
  lcd.write(lcd.num[10], 1);  // .
  lcd.write(lcd.num[2], 2);  // 2
  lcd.udcShow(1, 3);         // 心形
  
  lcd.write(lcd.num[4], 4);  // 4
  lcd.write(lcd.num[5], 5);  // 5
  lcd.write(lcd.num[6], 6);  // 6
  lcd.write(lcd.upper[21], 7); // V
  
  delay(2000);
}
