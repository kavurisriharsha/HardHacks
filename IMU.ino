#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

double getMagnitude(Adafruit_MPU6050 mpu);

int getMoving(int taskDuration) {
  int startTime = millis();
  int sampleSize = 0;
  double meanVal = 0;

  Serial.println("started");
  while (millis() < startTime + 2000) {
     sampleSize++;
     meanVal += getMagnitude(mpu);
  }

  meanVal = meanVal / sampleSize;
  Serial.println(meanVal);
  Serial.println("Start moving");

  bool taskCompleted = false;
  int completedFor = 0;
  
  while (!taskCompleted) {
    startTime = millis();
    
    while (millis() < startTime + taskDuration) {
      if (getMagnitude(mpu) > meanVal + 5) {
        completedFor = millis() - startTime;
        if (completedFor >= taskDuration) {
          taskCompleted = true;
          break;
        }
      }
    }
  }

  Serial.println("Task Completed");
  return 0;
}

double getMagnitude(Adafruit_MPU6050 mpu) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  double ab =  sqrt(a.acceleration.x * a.acceleration.x +
              a.acceleration.y * a.acceleration.y +
              a.acceleration.z * a.acceleration.z);
  Serial.println(ab);
  return ab;
}

void setup(void) {
  Serial.begin(115200);
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // Call getMoving with the desired task duration
  getMoving(5000);
}
