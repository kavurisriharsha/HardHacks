#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "RTClib.h"
#include <SoftwareSerial.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128 // OLED displaylay width, in pixels
#define SCREEN_HEIGHT 64 // OLED displaylay height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS1307 rtc;

SoftwareSerial BTSerial(2, 3); // RX, TX pins for SoftwareSerial

boolean isSet = false;

//String tasksArray[] = {"Time to Move!", "Press the button 10 times", "Wake up sleepy head!", "Can't sleep yet!"};

void setup() {
  Serial.begin(9600);
  
  rtc.begin();
  display.begin(i2c_Address, true); 
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  /*DateTime now = rtc.now();

  String received;
  int hrs, mins;*/
  
  
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Failure is always an option");
  display.display();
}
