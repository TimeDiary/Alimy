/*
  AlimyLib.h - Library for Alimy(Tableclock for 'hhmmss(TimeDiary)').
  Created by Jho. November 09, 2018.

  https://github.com/TimeDiary/Alimy.git
*/


#ifndef ALIMY_LIB_H
#define ALIMY_LIB_H

#include <LiquidCrystal_I2C.h> // For I2C_1602LCDmodule
#include <DS1302RTC.h> // For DS1302RTCmodule
#include <TimeLib.h> // For Time Control
#include "TM1637Display.h" // For 4digit display.

class Alimy
{
  public:
    /*
      Constructor

    */
    Alimy();

    /*
     * Init 1602LCD_I2C
     */
     int initLcd();


    /*
       Print String str to lcd's (0, 0)
    */
    int print2lcd(String);

    /*
       Print String str to lcd's (row, col)
    */
    int print2lcd(String, int, int);

    /*
       Clear lcd
    */
    int clearLcd();



  private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

    //    DS1302RTC RTC(uint8_t, uint8_t, uint8_t);


};

//class Alimy:
//  public void hi();
#endif // FDB_ALIMY_LIB_H

