#include <Arduino_LSM9DS1.h>
#include "MadgwickAHRS.h"

// Initialize Madgwick filter
Madgwick filter;
const float sensorRate = 104.00;

void setup() {
  Serial.begin(115200);  // Increase baud rate for faster communication
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    while (true);
  }
  
  filter.begin(sensorRate);
}

void loop() {
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;
  float roll, pitch, yaw;

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro);

    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);

    roll = filter.getRoll();
    pitch = filter.getPitch();
    yaw = filter.getYaw();

    // Output in CSV format
    Serial.print(roll); Serial.print(",");
    Serial.print(pitch); Serial.print(",");
    Serial.print(yaw); Serial.print(",");
    Serial.print(xGyro); Serial.print(",");
    Serial.print(yGyro); Serial.print(",");
    Serial.print(zGyro); Serial.print(",");
    Serial.print(xAcc); Serial.print(",");
    Serial.print(yAcc); Serial.print(",");
    Serial.println(zAcc);
  }
}
