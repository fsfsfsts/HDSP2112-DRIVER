#ifndef HDSP2112_h
#define HDSP2112_h

#include "Arduino.h"

#define DEFAULT_DIO 2
#define DEFAULT_CLK 3
#define DEFAULT_WR 4
#define DEFAULT_CE 5
#define DEFAULT_A0 6
#define DEFAULT_A1 7
#define DEFAULT_A2 8
#define DEFAULT_K4 21
#define DEFAULT_K3 22

class HDSP2112 {
  public:
    HDSP2112();
    HDSP2112(int dio, int clk, int wr, int ce, int a0, int a1, int a2, int k4, int k3);
    
    void begin();
    void write(byte dat, byte add);
    void control(byte dat);
    void udcDefine(byte num, const byte* pattern);
    void udcShow(byte num, byte pos);
    
    static const byte num[11];
    static const byte upper[27];
    static const byte lower[27];
    
  private:
    int _dio, _clk, _wr, _ce, _a0, _a1, _a2, _k4, _k3;
    void addr(byte x);
    void row(byte x, byte y, byte z);
};

extern const byte heart[7];

#endif
