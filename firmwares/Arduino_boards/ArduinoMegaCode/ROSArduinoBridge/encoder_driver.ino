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
  int lastStateLeftA;
  int lastStateRightA;

  /* Initialize encoder states */
  void initEncoders() {
    lastStateLeftA = digitalRead(LEFT_ENC_PIN_A);
    lastStateRightA = digitalRead(RIGHT_ENC_PIN_A);
  }

  /* Interrupt routine for LEFT encoder */
  void updateLeftEncoder() {
    int stateA = digitalRead(LEFT_ENC_PIN_A);
    int stateB = digitalRead(LEFT_ENC_PIN_B);

    if (stateA != lastStateLeftA) {
      if (stateA == stateB) {
        left_enc_pos++;  // Clockwise
      } else {
        left_enc_pos--;  // Counterclockwise
      }
    }

    lastStateLeftA = stateA;
  }

  /* Interrupt routine for RIGHT encoder */
  void updateRightEncoder() {
    int stateA = digitalRead(RIGHT_ENC_PIN_A);
    int stateB = digitalRead(RIGHT_ENC_PIN_B);

    if (stateA != lastStateRightA) {
      if (stateA == stateB) {
        right_enc_pos++;  // Clockwise
      } else {
        right_enc_pos--;  // Counterclockwise
      }
    }

    lastStateRightA = stateA;
  }

  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) {
      left_enc_pos = 0L;
    } else {
      right_enc_pos = 0L;
    }
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

