#include <DS1302RTC.h> //DS1302 라이브러리 헤더파일 포함

/*

  GND-GND

  VCC-5V

  CLK-D2

  DAT-D3

  RST-D4

*/
#define RTC_CLK 2
#define RTC_DAT 3
#define RTC_RST 4

DS1302 rtc(RTC_CLK, RTC_DAT, RTC_RST); // DS1302모듈을 init해주는 역할(init: 시스템이 종료될 때까지 계속 실행되는 데몬 프로세스)



void setup() {                    //초기설정

  Serial.begin(9600);      //시리얼 통신

  rtc.halt(false);               //시간을 run-mode로 설정

  rtc.writeProtect(false); // 쓰는 것을 방지하는 비활성화 역할

  //false로 설정해주어야 시간 설정을 자유롭게 할 수 있다. 00시00분00초가 되면 다시 reset되어 처음부터 카운팅



  // MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY

  rtc.setDOW (WEDNESDAY);        // 수요일(요일)

  rtc.setTime(23, 59, 30);              // 23시 59분 30초(시간)

  rtc.setDate(05, 04, 2017);        // 2017년 4월 5일 (날짜)

}

void loop() {                                        //무한 동작

  Serial.print(" Today is ");

  Serial.print(rtc.getDOWStr());    // 요일을 출력



  Serial.print(" -- ");

  Serial.print(rtc.getDateStr());   // 날짜를 출력



  Serial.print(" Time : ");

  Serial.println(rtc.getTimeStr());  // 시간을 출력



  delay (1000);  //1초마다 출력 시간 설정

}


