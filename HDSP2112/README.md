# HDSP2112 LCD 库

Arduino 库用于控制 HDSP2112 LCD 显示器，通过 74HC164D 移位寄存器实现。

## 特性

- 简洁的 API 接口
- 支持自定义字符
- 内置字符集（数字、大小写字母）
- 默认引脚配置

## 安装

将 `HDSP2112` 文件夹复制到 Arduino 库目录：
- Windows: `Documents\Arduino\libraries\`
- macOS: `Documents/Arduino/libraries/`
- Linux: `~/Arduino/libraries/`

## 基本使用

```cpp
#include <HDSP2112.h>

HDSP2112 lcd;

void setup() {
  lcd.begin();
}

void loop() {
  // 显示数字 0-7
  for (byte i = 0; i < 8; i++) {
    lcd.write(lcd.num[i], i);
  }
  delay(1000);
}
```

## API

### 初始化

```cpp
HDSP2112 lcd;              // 默认引脚
HDSP2112 lcd(dio,clk,wr,ce,a0,a1,a2,k4,k3);  // 自定义引脚
lcd.begin();               // 初始化
```

### 显示

```cpp
lcd.write(dat, add);       // 写数据到指定位置(0-7)
lcd.control(brightness);   // 设置亮度(0=100%, 7=0%)
lcd.udcShow(num, pos);     // 显示自定义字符
```

### 自定义字符

```cpp
const byte pattern[7] = {0x15,0x1F,0x13,0x0E,0x04,0x00,0x00};
lcd.udcDefine(1, pattern);  // 定义第1个自定义字符
lcd.udcShow(1, 0);          // 在位置0显示
```

## 字符集

| 名称 | 内容 | 示例 |
|------|------|------|
| `num` | 0-9 和 `.` | `lcd.num[0]` = '0' |
| `upper` | A-Z | `lcd.upper[0]` = 'A' |
| `lower` | a-z | `lcd.lower[0]` = 'a' |

## 硬件连接

| Arduino | 74HC164D | HDSP2112 |
|---------|----------|----------|
| D2 | DS | - |
| D3 | SH_CP | - |
| D4 | WR | - |
| D5 | CE | - |
| D6 | A0 | A0 |
| D7 | A1 | A1 |
| D8 | A2 | A2 |
| D21 | K4 | K4 |
| D22 | K3 | K3 |

## 示例

```cpp
#include <HDSP2112.h>

HDSP2112 lcd;

void setup() {
  lcd.begin();
}

void loop() {
  // 显示 "1.23V"
  lcd.write(lcd.num[1], 0);
  lcd.write(lcd.num[10], 1);  // .
  lcd.write(lcd.num[2], 2);
  lcd.write(lcd.num[3], 3);
  lcd.write(lcd.upper[21], 4);  // V
  
  delay(2000);
}
```

## 许可证

MIT
