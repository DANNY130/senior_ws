/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
#ifdef ARDUINO_ENC_COUNTER
  // Update these to match the Nano 33 BLE pinout
  #define LEFT_ENC_PIN_A 2  // D2
  #define LEFT_ENC_PIN_B 3  // D3
  
  #define RIGHT_ENC_PIN_A 4  // D4
  #define RIGHT_ENC_PIN_B 5  // D5
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();