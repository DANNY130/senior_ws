#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <Wire.h>
#include <INA226_WE.h>
#include "MadgwickAHRS.h"
#define I2C_ADDRESS 0x40

/**Proximity Sensor Vars**/
const int numSensors = 5;
const int trigPins[numSensors] = {2, 4, 6, 8, 10};
const int echoPins[numSensors] = {3, 5, 7, 9, 11};

/**SoC Vars**/
struct VoltageSoC {
  float voltage;  // voltage in V
  int soc;        // SoC as a percentage %
};

const VoltageSoC lookupTable_10[] = {
  { 12.220, 1 }, { 12.733, 7 }, { 12.827, 14 }, { 12.900, 21 }, { 12.956, 28 }, { 13.000, 35 }, { 13.060, 42 }, { 13.125, 57 }, { 13.143, 71 }, { 13.153, 78 }, { 13.186, 85 }, { 13.300, 92 }
};

const VoltageSoC lookupTable_30[] = {
  { 12.252, 1 }, { 12.755, 7 }, { 12.841, 14 }, { 12.918, 21 }, { 12.973, 28 }, { 13.018, 35 }, { 13.078, 42 }, { 13.141, 50 }, { 13.144, 57 }, { 13.150, 64 }, { 13.159, 71 }, { 13.169, 78 }, { 13.204, 85 }, { 13.300, 93 }
};

const int tableSize_10 = sizeof(lookupTable_10) / sizeof(lookupTable_10[0]);
const int tableSize_30 = sizeof(lookupTable_30) / sizeof(lookupTable_30[0]);



//Initialize INA226 object from I2C address (A0, A1 pins grounded)
INA226_WE ina226 = INA226_WE(I2C_ADDRESS);
float SHUNT_OHM = 0.0025;           // shunt resistor value (Ohms)
float IDLE_CURRENT = 1.0;  //quiescent current for ON device with battery connected

unsigned long sampleTime_us = micros();    // time in microseconds for power calculations
unsigned long prevTime_us = micros();

unsigned long idleTime_ms = 0;      // time in milliseconds for OCV lookup
const unsigned long US_H = 3.6e+9;  // global var for us in an hour

bool ocvFlag10 = false;
bool ocvFlag30 = false;  // for if/else battery voltage checking

float SoC_FULL_Ams = 21 * 3.6e+6;    // Ampere-millisecond charge at full 
float SoC_Ams = SoC_FULL_Ams;
int SoC_pct = 100;



// Initialize Madgwick filter for IMU
Madgwick filter;
const float sensorRate = 104.00;  // Sensor rate in Hz

/*------------------------------------------------------*/

void setup() {
  Serial.begin(115200);  // Increase baud rate for faster communication
  while (!Serial)
    ;  // Wait for serial port to connect. Needed for native USB port only

  if (!IMU.begin()) {  // Initialize IMU
    Serial.println("Failed to initialize IMU");
    while (true)
      ;
  }

  //Serial.println("IMU Initialized");

  filter.begin(sensorRate);  // Initialize filter with sensor rate


//check initializing ultrasonic sensors
//convention:
//1:
//2:
//3:
//4: Left Side
//5: 
  for (int i = 0; i < numSensors; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
  //Serial.println("Ultrasonic system online.");



  ///* -----waiting on hardware testing--------
  //Initialize INA226 parameters, see Lib for all value options
  //Serial.println("Initializing INA226");
  Wire.begin();
  //Serial.println("Wire Begun");
  ina226.init();
  //Serial.println("INA226 Initialized");
  ina226.setAverage(AVERAGE_16); // number of samples for shunt and bus voltage to be averaged.
  ina226.setConversionTime(CONV_TIME_332);     // time for each sample measurement in us. Time for 1 sample shuntV and busV = ct x 2
  ina226.setResistorRange(SHUNT_OHM, 32.768);  // choose resistor 2.5 mOhm and gain range up to 32.768 A. Current calculated from IC datasheet.
  //Serial.println("Conv time and Resistor range set - if stuck here INA226 disconnected");
  ina226.waitUntilConversionCompleted();       //if you comment this line the first data might be zero
  //Serial.println("Setup Complete");
  
  delay(50); //delay to ensure proper initialization of SoC
  SoC_pct = findNearestSoC(ina226.getBusVoltage_V(), lookupTable_30, tableSize_30) - 10.0;
  SoC_Ams = SoC_FULL_Ams / 100 * SoC_pct;
 // ------------------------------------------*/
}


void loop() {
  // Initialize variables for sensor data
  float xAcc, yAcc, zAcc;                     // Accelerometer data
  float xGyro, yGyro, zGyro;                  // Gyroscope data
  float roll, pitch, yaw;                     // Euler angles
  int sensorValue = 0;                        // variable to read analog pin value

  for (int i = 0; i < numSensors; i++) {

    float distance = readUltrasonicDistance(trigPins[i], echoPins[i]);

    // Serial.print(sensorLocations[i]);
    Serial.print(distance);
    Serial.print(",");
  }
  
 //------------POWER MONITOR------------------------
  float shuntVoltage_mV, busVoltage_V;        // values measured by INA226
  float supplyVoltage_V, current_A, power_W;  // values calculated, either by INA226 or by arduino
  float chargeChange_Ams = 0.0;  // 
  float tempCelsius = 0.0;                    // initialized to prevent false cooling alert
  uint8_t errorCode = 0;                      // error codes: 0 = allclear, 1 = overcurrent, 2 = negative current, 3 = undervoltage

  //Temperature Sensing
  sensorValue = analogRead(A0);
  tempCelsius = (3.3 * sensorValue / 1023.0 - 0.4) / .0195;  // V = 3.3V * Analog / 10bits, T = (V - 0.4)/(19.5mV/C)

  // Power Sensing
  ina226.readAndClearFlags();
  shuntVoltage_mV = ina226.getShuntVoltage_mV();
  busVoltage_V = ina226.getBusVoltage_V();
  supplyVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000);  // Voltage from battery / power supply
  current_A = shuntVoltage_mV / SHUNT_OHM / 1000;             // I=V/R
  
  //Deprecated methods due to faulty IC in test
  //power_W = supplyVoltage_V * current_A;
  //current_mA = ina226.getCurrent_mA();
  //power_mW = ina226.getBusPower();
  
  sampleTime_us = micros() - prevTime_us;  //  time in microseconds since last measurement
  if (current_A <= IDLE_CURRENT) {
    idleTime_ms += sampleTime_us / 1000;  //  start counting idle time in ms
  }
  else {
    idleTime_ms = 0;
  }

  //sets bool flags for 10min and 30min OCV check, battery monitor calibration
  //flags are TRUE if the measurement time has been exceeded and lookup is no longer ideal
  if (idleTime_ms > 1.9e+6){
    ocvFlag30 = true;
  }
  else if (idleTime_ms > 6e+5){
    ocvFlag30 = false;
    ocvFlag10 = true;
  }
  else {
    ocvFlag10 = ocvFlag30 = false;
  }

  // allow OCV_10 lookup after 8min and OCV_30 after 25min
  if (idleTime_ms > 4.8e+5 && !ocvFlag10){
    SoC_pct = findNearestSoC(busVoltage_V, lookupTable_10, tableSize_10);
    SoC_Ams = SoC_FULL_Ams / 100.0 * SoC_pct;
  }
  else if (idleTime_ms > 1.5e+6 && !ocvFlag30){
    SoC_pct = findNearestSoC(busVoltage_V, lookupTable_30, tableSize_30);
    SoC_Ams = SoC_FULL_Ams / 100 * SoC_pct;
  }

  //track current -> if current below threshold for 8-12min or 24-36min OCV check
  chargeChange_Ams = current_A * sampleTime_us / 1000;
  prevTime_us = micros();  // store current time in us
  
  SoC_Ams -= chargeChange_Ams;
  SoC_pct = SoC_Ams * 100 / SoC_FULL_Ams;


  if (current_A >= 25.0) {
    errorCode = 1;  //overcurrent
  } else if (current_A < -0.1) {
    errorCode = 2;  //reverse current
  } else if (supplyVoltage_V < 10.0) {
    errorCode = 3;  //undervoltage
  }

  Serial.print(tempCelsius); //Serial.print("C");
  Serial.print(","); 
  Serial.print(supplyVoltage_V); //Serial.print("V");
  Serial.print(","); 
  Serial.print(current_A); //Serial.print("A");
  Serial.print(",");
  Serial.print(SoC_pct); //Serial.print("%");
  Serial.print(",");
  Serial.print(errorCode);
 // -------------------------------------------



  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {  // Check if data is available
    // Read accelerometer and gyroscope data
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro);

    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);  // Update filter with new data
    // Get Euler angles from filter
    roll = filter.getRoll();
    pitch = filter.getPitch();
    yaw = filter.getYaw();

    // Output in CSV format
    Serial.print(",");
    Serial.print(roll);
    Serial.print(",");
    Serial.print(pitch);
    Serial.print(",");
    Serial.print(yaw);
    Serial.print(",");
    Serial.print(xGyro);
    Serial.print(",");
    Serial.print(yGyro);
    Serial.print(",");
    Serial.print(zGyro);
    Serial.print(",");
    Serial.print(xAcc);
    Serial.print(",");
    Serial.print(yAcc);
    Serial.print(",");
    Serial.print(zAcc);
  }

  Serial.println();

  //delay(1000); //for testing purposes
}


/**
*FUNCTION DEFINITION TODO
*
*
**/
int findNearestSoC(float inputVoltage, const VoltageSoC table[], int size) {
  if (inputVoltage > 13.4) return 100; //full battery
  if (size == 0) return 0;  // empty table

  int left = 0, right = size - 1;
  int closestIdx = -1;
  float minDiff = 3.4e+38f;  // near FLT_MAX without using libraries

  // Binary search to find the nearest voltage
  while (left <= right) {
    int mid = left + (right - left) / 2;                  // insertion point
    float diff = abs(table[mid].voltage - inputVoltage);  //difference from ref value

    // update selection criteria if new value is closer
    if (diff < minDiff) {
      minDiff = diff;
      closestIdx = mid;
    }

    if (inputVoltage < table[mid].voltage) {
      right = mid - 1;
    } else if (inputVoltage > table[mid].voltage) {
      left = mid + 1;
    } else {
      // Exact match
      return table[mid].soc;
    }
  }
  
  return table[closestIdx].soc;
}


float readUltrasonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 10000);
  // if (duration == 0) return -1.0;
  // return (duration / 2.0) / 29.1;

  if (duration == 0) {
    return -1.0;
  } else {
    return (duration / 2.0) / 29.1;
  }
}
