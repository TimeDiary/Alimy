#include <Arduino.h>
#include "AlimyLib.h"


Alimy::Alimy()
{
  lcd.begin();
  lcd.backlight();

}

Alimy::print2lcd(String str)
{
  lcd.setCursor(0, 0);
  lcd.print(str);
}

Alimy::print2lcd(String str, int row, int col)
{
  lcd.setCursor(col, row);
  lcd.print(str);

}

Alimy::clearLcd()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

