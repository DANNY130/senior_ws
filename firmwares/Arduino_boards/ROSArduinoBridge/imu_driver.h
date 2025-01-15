/* *************************************************************
   IMU driver function definitions - by Danny Pham
   ************************************************************ */

#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

// Define IMU pin assignments
#define IMU_SDA_PIN A4 // I2C SDA pin
#define IMU_SCL_PIN A5 // I2C SCL pin

// Function declarations
void setupIMU();
void readIMU();
void resetIMU();
void publishIMUState();

#endif // IMU_DRIVER_H