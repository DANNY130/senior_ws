/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */

#ifdef ARDUINO_ENC_COUNTER
  // Define encoder pins for Arduino Mega
  #define LEFT_ENC_PIN_A 2  // Digital pin 2
  #define LEFT_ENC_PIN_B 3  // Digital pin 3
  #define RIGHT_ENC_PIN_A 18 // Digital pin 18
  #define RIGHT_ENC_PIN_B 19 // Digital pin 19
#endif

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

