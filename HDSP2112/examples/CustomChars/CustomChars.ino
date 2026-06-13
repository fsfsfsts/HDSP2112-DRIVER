#include <HDSP2112.h>

HDSP2112 lcd;

// 自定义字符图案
const byte smile[7] = {0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x00};  // 笑脸
const byte music[7] = {0x04, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00};   // 音符
const byte arrow[7] = {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x00};  // 向上箭头
const byte battery[7] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F}; // 电池

void setup() {
  lcd.begin();
  
  // 定义自定义字符（最多16个，编号0-15）
  lcd.udcDefine(1, smile);   // 字符1 = 笑脸
  lcd.udcDefine(2, music);   // 字符2 = 音符
  lcd.udcDefine(3, arrow);   // 字符3 = 箭头
  lcd.udcDefine(4, battery); // 字符4 = 电池
  
  Serial.begin(115200);
  Serial.println("HDSP2112 自定义字符示例");
}

void loop() {
  // 显示自定义字符
  Serial.println("显示自定义字符");
  lcd.udcShow(1, 0);  // 笑脸
  lcd.udcShow(2, 1);  // 音符
  lcd.udcShow(3, 2);  // 箭头
  lcd.udcShow(4, 3);  // 电池
  delay(2000);
  
  // 显示混合内容
  Serial.println("显示混合内容");
  lcd.write(lcd.upper[19], 0);  // T
  lcd.write(lcd.lower[4], 1);   // i
  lcd.write(lcd.lower[0], 2);   // a
  lcd.write(lcd.lower[13], 3);  // n
  lcd.udcShow(1, 4);            // 笑脸
  lcd.write(lcd.num[1], 5);     // 1
  lcd.write(lcd.num[2], 6);     // 2
  lcd.write(lcd.num[3], 7);     // 3
  delay(2000);
  
  // 显示电池符号和电量
  Serial.println("显示电量");
  lcd.udcShow(4, 0);            // 电池
  lcd.write(lcd.num[8], 1);     // 8
  lcd.write(lcd.num[5], 2);     // 5
  lcd.write(0x25, 3);           // %
  delay(2000);
  
  // 清除屏幕
  for (byte i = 0; i < 8; i++) {
    lcd.write(0x20, i);  // 空格
  }
  delay(500);
}