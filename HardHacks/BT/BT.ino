#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX pins for SoftwareSerial

void setup() {
  Serial.begin(9600); // Serial monitor for debugging
  BTSerial.begin(9600); // Bluetooth module baud rate
  
  Serial.println("HC-05 Bluetooth Module Initialized");
}

void loop() {
  // Check if data is available on Bluetooth module
  String received;
  if (BTSerial.available()) {
    received = BTSerial.readString(); // Read the incoming byte from Bluetooth
    
    // Print the received character to Serial monitor
    Serial.print("Received: ");
    Serial.println(received);

    int hrs, mins, date;

    hrs = received.substring(0,received.indexOf(':')).toInt();

    mins = received.substring(received.indexOf(':')+1, received.indexOf('.')).toInt();
    date = received.substring(received.indexOf('.')+1, received.length()).toInt();

    Serial.println(hrs);
    Serial.println(mins);
    Serial.println(date);
    
  }
}
