#include <Arduino.h>
#include "AlimyLib.h"



Alimy::Alimy()
{



  //  lcd.begin();
  //  lcd.backlight();

}


Alimy::initLcd()
{
  lcd.begin();
  lcd.backlight();
}

Alimy::print2lcd(String str)
{
  lcd.setCursor(0, 0);
  lcd.print(str);
  //  Serial.println("[LCD] message: \" " + str + "\" printed.");
  return 0;
}

Alimy::print2lcd(String str, int row, int col)
{
  lcd.setCursor(col, row);
  lcd.print(str);
  //  Serial.print("[LCD] message: \" " + str + "\" printed.");
  //  Serial.println("to (" + String(row) + ", " + String(col) + ")");
  return 0;
}

Alimy::clearLcd()
{
  lcd.clear();
  lcd.setCursor(0, 0);

  return 0;
}

