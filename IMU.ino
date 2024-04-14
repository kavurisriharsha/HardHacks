#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

double getMagnitude();

int getMoving(int taskDuration) {
  unsigned long startTime = millis();
  int sampleSize = 0;
  double meanVal = 0;

  // Calculate the mean magnitude of stationary state
  Serial.println("Calibrating, stay still...");
  while (millis() - startTime < 2000) {
    sampleSize++;
    meanVal += getMagnitude();
  }
  meanVal /= sampleSize;
  Serial.print("Calibration complete. Mean value: ");
  Serial.println(meanVal);

  task:
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
      }
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

  return 0;
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

void setup(void) {
  Serial.begin(115200);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 Found!");
}

void loop() {
  getMoving(2000);  // Task duration of 2 seconds
  delay(10000);     // Wait for 10 seconds before the next task
}
