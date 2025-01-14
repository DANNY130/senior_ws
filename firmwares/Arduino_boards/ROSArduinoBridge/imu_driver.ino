#ifdef USE_BASE

#ifdef IMU
    #include "imu_driver.h"
    #include <Wire.h>
    #include <Arduino_LSM9DS1.h>

    void readIMU() {
        // Read the accelerometer    For Linear Acceleration (m/s^2)
        float x, y, z;
        if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(x, y, z);

            // Store the x, y, z data into a variable and return it
            float imuAcc[3] = {x, y, z};
            return imuAcc;
        }

        // Read gyroscope data      For Angular Velocity (degrees/s)
        float a,b,c;
        if (IMU.gyroscopeAvailable()) {
            IMU.readGyroscope(x, y, z);

            // Store the x, y, z data into a variable and return it
            float imuGyro[3] = {a, b, c};
            return imuGyro;
        }

        // // Read magnetometer data       For Magnetic Field (uT)
        // float d,e,f;
        // if (IMU.magneticFieldAvailable()) {
        //     IMU.readMagneticField(x, y, z);

        //     // Store the x, y, z data into a variable and return it
        //     float imuMag[3] = {d, e, f};
        //     return imuMag;
        // }

        
    }