void completedJingle() {
  tone(349, 10);
  delay(100);
  noTone(10);
  tone(466, 10);
  delay(100);
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

void setup() {
  // put your setup code here, to run once:
  completedJingle();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(349, 10);
  delay(100);
  noTone(10);
  tone(466, 10);
  delay(100);
  noTone(10);
  tone(587, 10, 100);
  noTone(10);

}
