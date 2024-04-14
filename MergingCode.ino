#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO


int led1 = 7; 
int led2 = 6;
int led3 = 8;
int led4 = 9;

int timeElapsed;

int buzzer1 = 10;
int countNumLeft = 0;
int countNumRight = 0;
int lastButtonStateLeft = HIGH;
int lastButtonStateRight = HIGH;
int BUTTON_PIN_LEFT = 5;
int BUTTON_PIN_RIGHT = 4;

String task = "";
int timeGap;
int taskNum;
String tasksArray[] = {"Time to Move for 10s !", "Press the button 10 times", "Wake up sleepy head!", "Can't sleep yet!"}; // index 2: blinking lights, index 3: vibration
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  display.begin(i2c_Address, true); 
  pinMode(led1, OUTPUT);   

  Serial.begin(9600);
  //buzzerSound();
  pinMode(BUTTON_PIN_LEFT, INPUT_PULLUP);
  //pinMode(BUTTON_PIN_RIGHT, INPUT_PULLUP);
  DisplayTask();

  timeElapsed = millis();

}

void loop() {
  timeElapsed = millis();
  // put your main code here, to run repeatedly:
  //timeGap = random(600000, 1200000);
  timeGap = random(3000, 10000);
  while (true) { 
   if (millis() == timeElapsed + timeGap){
      break;     
   }
  }
  delay(2000);
  taskNum = static_cast<int>(random(0, 3));
  task = tasksArray[taskNum];
  DisplayTask();
  if(taskNum==1){
    Serial.println("task1");
    moveTask();
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

// fucntion that counts the number pushButtons
void buttonPressTask() { 

  DisplayTask();
  
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
  while (true) { 
   if (millis() == timeElapsed + 1000) {
    timeElapsed = millis(); 
    break; 
  }
  } 
  digitalWrite(led1, LOW); 
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  while (true) { 
   if (millis() == timeElapsed + 1000) { 
    timeElapsed = millis();
    break; 
  }
  } 
}

void moveTask(){
  DisplayTask();
  Serial.println("Move");
}
