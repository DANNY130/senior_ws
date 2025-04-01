#include <Arduino_LSM9DS1.h>
#include "MadgwickAHRS.h"

// Initialize Madgwick filter
Madgwick filter;
const float sensorRate = 104.00; // Sensor rate in Hz

void setup() {
  Serial.begin(115200);  // Increase baud rate for faster communication
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only

  if (!IMU.begin()) { // Initialize IMU
    Serial.println("Failed to initialize IMU");
    while (true);
  }
  
  filter.begin(sensorRate); // Initialize filter with sensor rate
}

void loop() {
  // Initialize variables for sensor data
  float xAcc, yAcc, zAcc; // Accelerometer data
  float xGyro, yGyro, zGyro;  // Gyroscope data
  float roll, pitch, yaw; // Euler angles

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) { // Check if data is available
    // Read accelerometer and gyroscope data
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro);

    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc); // Update filter with new data 
    // Get Euler angles from filter
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
