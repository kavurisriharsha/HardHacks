#include "RTClib.h"

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

  while(!now.hour == hrs && !now.min == mins && isSet) {
    // lopgic here
    if (!now.hour == hrs && !now.min == mins) break;
  }

  isSet = false;
}
