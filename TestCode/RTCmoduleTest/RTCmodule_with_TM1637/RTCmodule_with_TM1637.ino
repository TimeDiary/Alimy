#include <DS1302RTC.h>
#include <TimeLib.h>
#include <TM1637Display.h>


/* Settings for DS1302RTC */
// Set pin number for DS1302
#define RTC_CLK 8
#define RTC_DAT 9
#define RTC_RST 10

// Optional connection for RTC module
#define DS1302_GND_PIN 11
#define DS1302_VCC_PIN 12

// Variable for RTC module
DS1302RTC RTC(RTC_CLK, RTC_DAT, RTC_RST);
/* End of settings for DS1302RTC */

/* Settings for TM1637 */
// Set pin number for TM1637
#define TM1637_CLK 6
#define TM1637_DIO 7

// Variable for TM1637
TM1637Display digit(TM1637_CLK, TM1637_DIO);
/* End of settings for TM1637 */


/* declare functions */
//print date and time to Serial
void printDateTime(time_t);

//print date to Serial
void printDate(time_t);

//print time to Serial
void printTime(time_t);

//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim);

// Init RTC module.
void initRTC();

// Init TM1637 digit module.
void initTM1637();

// Print time to digit.
void printTime2digit(time_t);
/* End of decalre functions */

// temp varaible for test...
int colon;


void setup(void)
{
  Serial.begin(9600);

  colon = 1;

  initRTC();

  initTM1637();


}
void loop(void)
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  //check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
  if (Serial.available() >= 12) {
    //note that the tmElements_t Year member is an offset from 1970,
    //but the RTC wants the last two digits of the calendar year.
    //use the convenience macros from Time.h to do the conversions.
    int y = Serial.parseInt();

    if (y >= 100 && y < 1000)
      Serial.println("Error: Year must be two digits or four digits!");

    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else    //(y < 100)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      //use the time_t value to ensure correct weekday is set
      if (RTC.set(t) == 0) { // Success
        setTime(t);

        Serial.println("RTC set to: ");
        printDateTime(t);
        Serial.println();
      }
      else
        Serial.println();

      Serial.println("RTC set failed!");

      //dump any extraneous input
      while (Serial.available() > 0) Serial.read();
    }
  }

  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    printTime2digit(t);


    Serial.println();
  }
}



//print date and time to Serial
void printDateTime(time_t t)
{
  Serial.println();
  Serial.println("----------------------");
  printDate(t);
  printTime(t);
  Serial.println();
  Serial.println("----------------------");
  Serial.println();
}

//print time to Serial
void printTime(time_t t)
{
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');
}

//print date to Serial
void printDate(time_t t)
{
  Serial.print(year(t), DEC);
  Serial.print(".");
  Serial.print(monthShortStr(month(t)));
  Serial.print(".");
  printI00(day(t), 0);
  Serial.println();

}


//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
  if (val < 10) Serial.print("0");
  Serial.print(val, DEC);

  if (delim > 0) Serial.print(delim);

  return;

}

// Init RTC module.
void initRTC() {
  Serial.println("--------------------------------------");
  Serial.println("Start to initialize RTC module...");
  Serial.println();
  // Activate RTC module
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);

  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  Serial.println("RTC module activated");
  delay(500);

  if (RTC.haltRTC()) {
    Serial.println("The DS1302 is stopped.  Please set time");
    Serial.println("to initialize the time and begin running.");
    Serial.println();
  }
  if (!RTC.writeEN()) {
    Serial.println("The DS1302 is write protected. This normal.");
    Serial.println();

  }

  delay(5000);

  //setSyncProvider() causes the Time library to synchronize with the
  //external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(RTC.get);

  Serial.println("RTC Sync");
  if (timeStatus() == timeSet)
    Serial.println(" Ok!");
  else
    Serial.println(" FAIL!");

  Serial.println();
  Serial.println("Finished to initalize RTC module...");
  Serial.println("-----------------------------------");
}

// Init TM1637 digit module.
void initTM1637() {
  Serial.println("-----------------------------------");
  Serial.println("Start to init TM1637...");
  Serial.println();

  // Activate TM1637 digit module.
  digit.setBrightness(5);
  digit.showNumberDecEx(1234, 0x40);

  Serial.println();
  Serial.println("Finished to initalize RTC module...");
  Serial.println("-----------------------------------");


}

// Print time to digit.
void printTime2digit(time_t t)
{

  int tmp;
  tmp = hour(t) * 100;
  tmp += minute(t);
  if (colon == 1) {
    digit.showNumberDecEx(tmp, 0x40, true);
    colon = 0;
  } else {
    digit.showNumberDecEx(tmp, 0, true);
    colon = 1;
  }
}




