/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A PC4  //pin A4
  #define RIGHT_ENC_PIN_B PC5   //pin A5
#endif

#ifdef ESP32_ENC_COUNTER
    
  // ESP32 GPIO pins for encoders
  #define LEFT_ENC_A 16
  #define LEFT_ENC_B 17
  #define RIGHT_ENC_A 26
  #define RIGHT_ENC_B 27
#endif

#ifdef ESP32_ENC_COUNTER
  void setupEncoders();
#endif

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();
