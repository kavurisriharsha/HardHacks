#include <ezBuzzer.h> // ezBuzzer library
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

int led1 = 7; 
int led2 = 6;
int led3 = 8;
int led4 = 9;

int timeElapsed = 0;
timeElapsed = millis();
const int BUZZER_PIN = 10;
int buzzer1 = 10;
int countNumLeft = 0;
int countNumRight = 0;
int lastButtonStateLeft = HIGH;
int lastButtonStateRight = HIGH;
int BUTTON_PIN_LEFT = 5;
int BUTTON_PIN_RIGHT = 4;
ezBuzzer buzzer(BUZZER_PIN); // create ezBuzzer object that attach to a pin;
// notes in the melody:
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
  
};

int noteLength;

String task = "";
int timeGap;
int taskNum;
String tasksArray[] = {"Time to Move for 10s !", "Press the button 10 times", "Wake up sleepy head!", "Can't sleep yet!"}; // index 2: blinking lights, index 3: vibration
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(i2c_Address, true); 
  pinMode(led1, OUTPUT);   

  Serial.begin(9600);
  noteLength = sizeof(noteDurations) / sizeof(int);
  //buzzerSound();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
  while(true){
    timeGap = random(3000, 10000);
    delay(timeGap);
    taskNum = static_cast<int>(random(0, 4));
    task = tasksArray[taskNum];
    DisplayTask();
    taskIdentifier(taskNum); 
  }

}


// function that identifies what task to execute
void taskIdentifier(int randomNum) { 
  //String possibleTasks[] = {LRCombSound, LRCombLight, WalkCombSound, WalkCombLight} 
  //int randomNum = random(0,4);
  switch(randomNum) { 
    case '0':
      buzzerSound();
      moveTask();
      //void taskButton(); 
    case '1':
      buzzerSound();
      buttonPressTask();
    case '2':
      blinkLED(); 
      
    case '3':
      vibration();
   
  }
  
 
}

void DisplayTask(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
  // Display static text
    display.setCursor(35,10);
    display.println(task);
    display.display();
}

void moveTask(){

}

// fucntion that counts the number pushButtons
void buttonPressTask() { 
  
  int currentStateLeft = digitalRead(BUTTON_PIN_LEFT);
  int currentStateRight = digitalRead(BUTTON_PIN_RIGHT);  

  while(true){
      if(lastButtonStateLeft == HIGH && currentStateLeft == LOW) {
      countNumLeft++;
      lastButtonStateLeft = currentStateLeft; 
    }
    else if(lastButtonStateRight == HIGH && currentStateRight == LOW) {
      countNumRight++;
      lastButtonStateRight = currentStateRight; 
    }

    if(countNumLeft==5 && countNumRight==5){
      break;
    }
  }
  
}

void blinkLED() { 
  digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  while (True) { 
   if (millis() == timeElapsed + 250) {
    timeElapsed = millis(); 
    break; 
  }
  } 
  digitalWrite(led1, LOW); 
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  while (True) { 
   if (millis() == timeElapsed + 250) { 
    timeElapsed = millis();
    break; 
  }
  } 
}

void vibration(){

}


// function that plays melody
//void buzzerStart() { 
// buzzer.loop(); // MUST call the buzzer.loop() function in loop()
// buzzer.playMelody(melody, noteDurations, noteLength); // playing
//}
// function that beeps x beats
void buzzerSound(){
 tone(buzzer1, 600);
 while (True) { 
   if (millis() == timeElapsed + 250) { 
    timeElapsed = millis();
    break; 
  }
  } 
 noTone(buzzer1);
 tone(buzzer1, 600);
 while (True) { 
   if (millis() == timeElapsed + 250) { 
    timeElapsed = millis();
    break; 
  }
  } 
 noTone(buzzer1);


}
