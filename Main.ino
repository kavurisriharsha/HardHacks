#include "RTClib.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <U8x8lib.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128 // OLED displaylay width, in pixels
#define SCREEN_HEIGHT 64 // OLED displaylay height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

#define BUTTON_LEFT 5
#define BUTTON_RIGHT 9


U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

SoftwareSerial BTSerial(2, 3); // RX, TX pins for SoftwareSerial

RTC_DS1307 rtc;

int led1 = 6; 
int led2 = 7;
int led3 = 8;
int led4 = 9;

const int ledPins[] = {6, 7, 8, 9};

bool isSet;

Adafruit_MPU6050 mpu;

double getMagnitude();

//String tasksArray[] = {"Time to Move!", "Press the button 10 times", "Wake up sleepy head!", "Can't sleep yet!"}; // index 2: blinking lights, index 3: vibration

void displayText(char* text, int font) {
  u8x8.clear();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1,text);
  u8x8.refreshDisplay();  
}

void completedJingle() {
  tone(349, 10, 100);
  noTone(10);
  tone(466, 10, 100);
  noTone(10);
  tone(587, 10, 100);
  noTone(10);
  return;
}

void alertJingle() {
  tone(466, 10, 50);
  noTone(10);
  tone(466, 10, 50);
  noTone(10);
}

int moveTask(int taskDuration) {
  unsigned long startTime = millis();
  int sampleSize = 0;
  double meanVal = 0;

  //alertJingle();
  // Calculate the mean magnitude of stationary state
  Serial.println("Calibrating, stay still...");
  
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
        //completedJingle();
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

void buttonTask() {
  int leftPresses, rightPresses;
  leftPresses = (int)random(2,10);
  rightPresses = 10 - leftPresses;

  alertJingle();
  displayText(String("Press Left:"+String(leftPresses)+" Right:"+String(rightPresses)).c_str(), 1);
  
  int start = millis();

  int left = 0;
  int right = 0;

  boolean punish = false;

  while (left<=leftPresses && right<=rightPresses) {
    if (punish) tone(440, 10);
    if (left > leftPresses || right > rightPresses) {
      left = 0;
      right = 0;
      punish = true;
    }
    if (millis() > start + 5000) {
      punish = true;
    }

    if (digitalRead(BUTTON_LEFT)) left++;
    if (digitalRead(BUTTON_RIGHT)) right++;
  }

  noTone(10);

  displayText("Well done!", 2);
  delay(1000);
  
}

void lightTask() {
  alertJingle();
  displayText("Flashbang!", 1);
  delay(1000);
  int start = millis();

  while (millis() < start + 5000) {
    for (int i = 0; i < 5; i++) {  // 5-second animation
      // Turn on a random LED
      int randomLed = random(4);
      digitalWrite(ledPins[randomLed], HIGH);
  
      // Delay for a short period
      delay(20);
  
      // Turn off all LEDs
    }
    
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPins[j], LOW);
      delay(20);
    }
  }
  completedJingle();
}


void pickTask() {
  int task = (int) random(3);
  Serial.println(task);

  switch (task) {
    case 1:
      //moveTask(5000);
      lightTask();
      break;

    case 2:
      buttonTask();
      break;

    case 3:
      lightTask();
      break;
    
  }
  
}
/*
double getMagnitude() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  double magnitude = sqrt(a.acceleration.x * a.acceleration.x +
                          a.acceleration.y * a.acceleration.y +
                          a.acceleration.z * a.acceleration.z);
  //Serial.println(magnitude);
  return magnitude;
}*/

void setup() {
  Serial.begin(9600);

  BTSerial.begin(9600);
  /*if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }*/
  /*mpu.begin();
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);*/

  /*if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }*/
  /*Serial.println("display begin");
  delay(1000);
  display.begin(i2c_Address, true); 
  display.display();
  delay(2000);
  display.clearDisplay();*/
  Serial.println("test");
  rtc.begin();
  u8x8.begin();
  u8x8.setPowerSave(0);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  tone(10, 440);

  

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  lightTask();
  completedJingle();
  
  
   
}

void loop() {
  DateTime now = rtc.now();
  DateTime setTime = rtc.now();

  String received;
  int hrs, mins, date;
  
  
  Serial.println("Loop start");
  //display.clearDisplay();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1,"Set time in app");
  u8x8.refreshDisplay();
  
  if (BTSerial.available()) {
    Serial.println("bt");
    received = BTSerial.readString(); 
    //display.clearDisplay();

    //displayText("Time Set:\n", 2);
    u8x8.clear();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.drawString(0,1,String("Time Set: "+received.substring(0, received.indexOf('.'))).c_str());
    u8x8.refreshDisplay();
    delay(2000);
    /*display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.print("Time Set:\n");
    display.print(received.substring(0, received.indexOf('.')));
    display.display();
    delay(2000);*/
    
    hrs = received.substring(0,received.indexOf(':')).toInt();
    mins = received.substring(received.indexOf(':')+1, received.length()).toInt();
    date = received.substring(received.indexOf('.')+1, received.length()).toInt();
    setTime = DateTime(now.year(), now.month(), date, hrs, mins, 0);
    isSet = true;
  }

  //Serial.println(now.hour());
  //Serial.println(now.minute());
  if (isSet) Serial.println("set");
  if (now.unixtime()-setTime.unixtime() > 0) Serial.println("true");
  //delay(100);
  while(now.unixtime()-setTime.unixtime() > 0 && isSet) {
    //if (now.unixtime()-setTime.unixtime() < 0) break;
    // logic here
    Serial.println("test");
    displayText("Good luck!", 2);
    delay(((int)random(0.10, 0.20))*60000);
    pickTask();

    
    
  }

  /*displayText("Sweet dreams!", 2);
  delay(2000);*/
  //isSet = false;
}
