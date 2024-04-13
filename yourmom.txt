#include <SoftwareSerial.h>

// RX, TX connected to the TX, RX pins of the Bluetooth module
SoftwareSerial bluetoothSerial(10, 11); // RX, TX

void setup() {
  // Start communication with the computer and to Bluetooth module
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  Serial.println("Ready to receive time data...");
}

void loop() {
  // Check if data has been received from the Bluetooth module
  if (bluetoothSerial.available() > 0) {
    // Read the incoming time string
    String timeString = bluetoothSerial.readStringUntil('\n');
    
    // Optional: parse the timeString to extract hours, minutes, and seconds
    int hour = timeString.substring(0, 2).toInt();
    int minute = timeString.substring(3, 5).toInt();
    int second = timeString.substring(6, 8).toInt();

    // Display the received and parsed time
    Serial.print("Received Time: ");
    Serial.print(timeString);
    Serial.print(" - Parsed as: ");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);
  }
}

