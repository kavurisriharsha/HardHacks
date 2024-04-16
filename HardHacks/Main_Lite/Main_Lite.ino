#include "RTClib.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ss_oled.h>

#define USE_BACKBUFFER

#ifdef USE_BACKBUFFER
static uint8_t ucBackBuffer[1024];
#else
static uint8_t *ucBackBuffer = NULL;
#endif

#define SDA_PIN A4
#define SCL_PIN A5
#define RESET_PIN -1
#define OLED_ADDR -1
#define FLIP180 0
#define INVERT 0
#define USE_HW_I2C 0
#define MY_OLED OLED_128x64
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define BUTTON_LEFT 5
#define BUTTON_RIGHT 4

SSOLED ssoled;

SoftwareSerial BTSerial(2, 3); // RX, TX pins for SoftwareSerial

RTC_DS1307 rtc;

int led1 = 6; 
int led2 = 7;
int led3 = 8;
int led4 = 9;

bool isSet;

Adafruit_MPU6050 mpu;

double getMagnitude();

/*void displayText(char* text, int font) {
  display.clearDisplay();
  display.setTextSize(font);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.print(text);
  display.display();
}*/

/*int moveTask(int taskDuration) {
  unsigned long startTime = millis();
  int sampleSize = 0;
  double meanVal = 0;

  displayText("Calibrating, stay still...", 1);
  while (millis() - startTime < 2000) {
    sampleSize++;
    meanVal += getMagnitude();
  }
  meanVal /= sampleSize;
  Serial.print("Calibration complete. Mean value: ");
  Serial.println(meanVal);
  int i = 0;
  task:
  if (i > 0) tone(10, 440);
  displayText("Better start moving!", 1);
  Serial.println("Start moving for the task...");
  startTime = millis();  // Reset start time for the task
  bool taskCompleted = false;
  double sumMagnitude = 0; // Variable to store sum of magnitudes

  // Check for continuous movement over threshold
  
  while (!taskCompleted && (millis() - startTime < taskDuration)) {
    double magnitude = getMagnitude();
    sumMagnitude += magnitude; // Accumulate magnitude values

    if (magnitude > meanVal + 1) {
      // Movement detected, increment the completion time
      if (millis() - startTime >= taskDuration) {
        // Sustained movement over the duration
        taskCompleted = true;
        Serial.println("Task Completed");
        displayText("Task Completed!", 1);
      }
      displayText("Keep going...", 2);
    } else {
      // No movement, reset the start time
      //startTime = millis();
    }
  }

  // Calculate the mean magnitude of movement during the task
  double meanMagnitude = sumMagnitude / sampleSize;
  Serial.print("Mean magnitude during task: ");
  Serial.println(meanMagnitude);

  if(meanMagnitude < meanVal + 1) goto task;

  noTone(10);
  return 0;
}*/

void pickTask() {
  int task = (int) random(1,3);

  switch (task) {
    case 1:
      //moveTask(5000);
      break;

    case 2:
      //buttonTask();
      break;

    case 3:
      //lightTask();
      break;
    
  }
}

double getMagnitude() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  double magnitude = sqrt(a.acceleration.x * a.acceleration.x +
                          a.acceleration.y * a.acceleration.y +
                          a.acceleration.z * a.acceleration.z);
  //Serial.println(magnitude);
  return magnitude;
}

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  int rc;
// The I2C SDA/SCL pins set to -1 means to use the default Wire library
// If pins were specified, they would be bit-banged in software
// This isn't inferior to hw I2C and in fact allows you to go faster on certain CPUs
// The reset pin is optional and I've only seen it needed on larger OLEDs (2.4")
//    that can be configured as either SPI or I2C
//
// oledInit(SSOLED *, type, oled_addr, rotate180, invert, bWire, SDA_PIN, SCL_PIN, RESET_PIN, speed)

  rc = oledInit(&ssoled, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 400000L); // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND)
  {
    char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D"};
    oledFill(&ssoled, 0, 1);
    oledWriteString(&ssoled, 0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    oledSetBackBuffer(&ssoled, ucBackBuffer);
    delay(2000);
  }

  rtc.begin();
  mpu.begin();
  oledFill(&ssoled, 0x0, 1);

  oledWriteString(&ssoled, 0,16,0, (char *)"Test", FONT_NORMAL, 0, 1);
  delay(1000);
  Serial.println("test");
}

void loop() {
  DateTime now = rtc.now();
  DateTime setTime = rtc.now();

  oledFill(&ssoled, 0x0, 1);
  oledWriteString(&ssoled, 0,16,0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
  oledWriteString(&ssoled, 0,0,3,(char *)"**Demo**", FONT_LARGE, 0, 1);
  Serial.println("10");
  delay(2000);

  char received[20];
  int hrs, mins, date;
    
  if (true /*BTSerial.available()*/) {
    BTSerial.readBytes(received, 20); 
    /*display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.print("Time Set:\n");
    display.print(received);
    display.display();
    delay(2000);*/
    
    hrs = atoi(strtok(received, ":"));
    mins = atoi(strtok(NULL, "."));
    date = atoi(strtok(NULL, "."));

    setTime = DateTime(now.year(), now.month(), date, hrs, mins, 0);
    isSet = true;
  }

  while(now.unixtime()-setTime.unixtime() > 0 && isSet) {
    // logic here
  }
}
