#include "RTClib.h"
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX pins for SoftwareSerial

RTC_DS1307 rtc;

bool isSet;

void setup() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
}

void loop() {
  DateTime now = rtc.now();

  String received;
  int hrs, mins;
  
  if (BTSerial.available()) {
    received = BTSerial.readString(); 

    hrs = received.substring(0,received.indexOf(':')).toInt();
    mins = received.substring(received.indexOf(':')+1, received.length()).toInt();
    isSet = true;
  }

  
  while(!now.hour == hrs && !now.min == mins && isSet) {
    if (!now.hour == hrs && !now.min == mins) break;
    // logic here
    
  }

  isSet = false;
}
