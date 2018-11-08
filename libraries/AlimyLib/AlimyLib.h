#ifndef ALIMY_LIB_H
#define ALIMY_LIB_H

#include <LiquidCrystal_I2C.h> // For I2C_1602LCDmodule
#include <DS1302RTC.h> // For DS1302RTCmodule
#include <TimeLib.h> // For Time Control
#include "TM1637Display.h" // For 4digit display.

class Alimy
{
  public:
    static void hi();
};

//class Alimy:
//  public void hi();
#endif // FDB_ALIMY_LIB_H

