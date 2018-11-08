
#include "AlimyLib.h"

Alimy alimy;


void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  alimy.initLcd();
  alimy.print2lcd("bye");
  Serial.println("Start2.");






}

void loop() {
  // put your main code here, to run repeatedly:
  alimy.print2lcd("HI");
  delay(1000);
  alimy.clearLcd();
  delay(1000);
}
