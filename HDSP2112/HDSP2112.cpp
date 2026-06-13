#include "HDSP2112.h"

const byte heart[7] = {0x15, 0x1F, 0x13, 0x0E, 0x04, 0x00, 0x00};

const byte HDSP2112::num[11] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2E};
const byte HDSP2112::upper[27] = {0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A};
const byte HDSP2112::lower[27] = {0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A};

HDSP2112::HDSP2112() {
  _dio=DEFAULT_DIO; _clk=DEFAULT_CLK; _wr=DEFAULT_WR; _ce=DEFAULT_CE;
  _a0=DEFAULT_A0; _a1=DEFAULT_A1; _a2=DEFAULT_A2; _k4=DEFAULT_K4; _k3=DEFAULT_K3;
}

HDSP2112::HDSP2112(int dio, int clk, int wr, int ce, int a0, int a1, int a2, int k4, int k3) {
  _dio=dio; _clk=clk; _wr=wr; _ce=ce; _a0=a0; _a1=a1; _a2=a2; _k4=k4; _k3=k3;
}

void HDSP2112::row(byte x, byte y, byte z) {
  digitalWrite(_a0, x ? HIGH : LOW);
  digitalWrite(_a1, y ? HIGH : LOW);
  digitalWrite(_a2, z ? HIGH : LOW);
}

void HDSP2112::addr(byte x) {
  const byte t[8][3] = {{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
  row(t[x][0], t[x][1], t[x][2]);
}

void HDSP2112::begin() {
  pinMode(_dio, OUTPUT); pinMode(_clk, OUTPUT); pinMode(_wr, OUTPUT);
  pinMode(_ce, OUTPUT); pinMode(_a0, OUTPUT); pinMode(_a1, OUTPUT);
  pinMode(_a2, OUTPUT); pinMode(_k3, OUTPUT); pinMode(_k4, OUTPUT);
  udcDefine(1, heart);
  delayMicroseconds(50);
}

void HDSP2112::write(byte dat, byte add) {
  digitalWrite(_k3, HIGH); digitalWrite(_k4, HIGH);
  digitalWrite(_ce, LOW); digitalWrite(_wr, HIGH);
  addr(add);
  shiftOut(_dio, _clk, MSBFIRST, dat);
  delay(1); digitalWrite(_wr, LOW); delayMicroseconds(1);
  digitalWrite(_ce, HIGH);
}

void HDSP2112::control(byte dat) {
  digitalWrite(_k3, LOW); digitalWrite(_k4, HIGH);
  digitalWrite(_ce, LOW); digitalWrite(_wr, HIGH);
  shiftOut(_dio, _clk, MSBFIRST, 0);
  shiftOut(_dio, _clk, MSBFIRST, 8 + dat);
  delay(1); digitalWrite(_wr, LOW); delayMicroseconds(1);
  digitalWrite(_ce, HIGH);
}

void HDSP2112::udcDefine(byte num, const byte* pattern) {
  digitalWrite(_k3, LOW); digitalWrite(_k4, LOW);
  digitalWrite(_ce, LOW); digitalWrite(_wr, HIGH);
  addr(0); shiftOut(_dio, _clk, MSBFIRST, num & 0x0F);
  delay(1); digitalWrite(_wr, LOW); delayMicroseconds(1); digitalWrite(_ce, HIGH);
  
  digitalWrite(_k3, HIGH); digitalWrite(_k4, LOW);
  digitalWrite(_ce, LOW); digitalWrite(_wr, HIGH);
  for (byte i = 0; i < 7; i++) {
    addr(i); shiftOut(_dio, _clk, MSBFIRST, pattern[i] & 0x1F);
    delay(1); digitalWrite(_wr, LOW); delayMicroseconds(1);
    digitalWrite(_ce, HIGH); digitalWrite(_ce, LOW); digitalWrite(_wr, HIGH);
  }
}

void HDSP2112::udcShow(byte num, byte pos) {
  write(0x80 | (num & 0x0F), pos);
}
