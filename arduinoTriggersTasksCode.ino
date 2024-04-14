int led1 = 7; 
int led2 = 6;
int led3 = 8;
int led4 = 9;

#include <ezBuzzer.h> // ezBuzzer library
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

void setup() {
  pinMode(led1, OUTPUT);   

  Serial.begin(9600);
  noteLength = sizeof(noteDurations) / sizeof(int);
  //buzzerSound();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
void taskIdentifier(); 

}


// function that identifies what task to execute
void taskIdentifier() { 
  String possibleTasks[] = {LRCombSound, LRCombLight, WalkCombSound, WalkCombLight} 
  int randomNum = random(0,4);
  switch(randomNum) { 
    case '0':
      void buzzerSound();
      void taskButton(); 
    case '1':
      void blinkLED(); 
      void taskButton(); 
    case '2':
      void buzzerSound(); 
      // walking function;
      
    case '3':
      void blinkLED(); 
      // walking function;
   
  }
  
 
}
// function task 1
void LRCombSound() { 
  
}
// function task 2
void LRCombLight() { 
  
}
// function task 3
void WalkCombSound() { 
  
}
void WalkCombLight() { 
  
}
// trigger one: lights flashing
// trigger two: sound beeping


// function task 4
// function that blinks light
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
// fucntion that counts the number pushButtons
void buttonCountLeft() { 
  int currentStateLeft = digitalRead(BUTTON_PIN_LEFT); 

  if (lastButtonStateLeft == HIGH && currentStateLeft == LOW) {
    countNumLeft++;
  }
  lastButtonStateLeft = currentStateLeft; 
  
}

void buttonCountRight() { 
  int currentStateRight = digitalRead(BUTTON_PIN_RIGHT); 

  if (lastButtonStateRight == HIGH && currentStateRight == LOW) {
    countNumRight++;
  }
  lastButtonStateRight = currentStateRight; 
  
}
