#ifdef USE_BASE

#ifdef IMU
    #include "imu_driver.h"
    #include <Wire.h>
    #include <Arduino_LSM9DS1.h>

    float* readIMU(float* imuData) {
        // Read the accelerometer    For Linear Acceleration (m/s^2)
        float x, y, z;
        if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(x, y, z);
        }

        // Read gyroscope data      For Angular Velocity (degrees/s)
        float a, b, c;
        if (IMU.gyroscopeAvailable()) {
            IMU.readGyroscope(a, b, c);
        }

        // // Read orientation data    For Orientation (quaternion)
        // float qx, qy, qz, qw;
        // if (IMU.orientationAvailable()) {
        //     IMU.readOrientation(qx, qy, qz, qw);
        // }

        // Store the x, y, z, a, b, c, qx, qy, qz, qw data into a variable and return it
        imuData[0] = x;
        imuData[1] = y;
        imuData[2] = z;
        imuData[3] = a;
        imuData[4] = b;
        imuData[5] = c;
        // imuData[6] = qx;
        // imuData[7] = qy;
        // imuData[8] = qz;
        // imuData[9] = qw;
        
        return imuData;
    }

    void setupIMU() {
        if (!IMU.begin()) {
            Serial.println("Failed to initialize IMU!");
            // Retry initialization
            for(int i = 0; i < 5; i++) {
                if (IMU.begin()) {
                    imuInitialized = true;
                    return;
                }
                delay(100);
            }
            // If we still can't initialize the IMU, set the flag to false
            imuInitialized = false;
            Serial.println("IMU initialization failed.");
        } else {
            imuInitialized = true;
        }
    }
#endif

#endif