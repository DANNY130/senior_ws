/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t enc_last=0;
          	
	enc_last <<=2; //shift previous state two places
	enc_last |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#elif defined ESP32_ENC_COUNTER

  #include <ESP32Encoder.h>
  
  extern bool loopTaskWDTEnabled;
  extern TaskHandle_t loopTaskHandle;

  // Callback function for encoder interrupts
  static IRAM_ATTR void enc_cb(void* arg) {
    ESP32Encoder* enc = (ESP32Encoder*) arg;
    // add any immediate processing here if needed
    // For example, toggle an LED to visualize encoder activity:
    // static bool led_state = false;
    // digitalWrite(LED_BUILTIN, led_state);
    // led_state = !led_state;
  }

  ESP32Encoder leftEncoder(true, enc_cb);
  ESP32Encoder rightEncoder(true, enc_cb);
  
  void setupEncoders() {

    // Enable the weak pull up resistors
    ESP32Encoder::useInternalWeakPullResistors = puType::up;
    
    // Configure encoder pins
    leftEncoder.attachSingleEdge(LEFT_ENC_A, LEFT_ENC_B);
    rightEncoder.attachSingleEdge(RIGHT_ENC_A, RIGHT_ENC_B);
    
    // Clear encoder counts
    leftEncoder.clearCount();
    rightEncoder.clearCount();

    // Clear encoder counts
    leftEncoder.setFilter(127);
    rightEncoder.setFilter(127);
        
  }

  long readEncoder(int i) {
    if (i == LEFT) return -(leftEncoder.getCount());
    else return rightEncoder.getCount();
  }

  void resetEncoder(int i) {
    if (i == LEFT) leftEncoder.clearCount();
    else rightEncoder.clearCount();
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif
