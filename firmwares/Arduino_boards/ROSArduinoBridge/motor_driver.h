/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
   #define RIGHT_MOTOR_BACKWARD 5
   #define LEFT_MOTOR_BACKWARD 6
   #define RIGHT_MOTOR_FORWARD 9
   #define LEFT_MOTOR_FORWARD 10
   #define RIGHT_MOTOR_ENABLE 12
   #define LEFT_MOTOR_ENABLE 13

#elif defined DM542T
   /* Minimum delay in microseconds between step pulses for Stepper motor*/
   #define MIN_STEP_DELAY 10
   // Define motor1 GPIO pins
   #define MOTOR1_STEP_PIN 9    // Step signal (GPIO 21, PUL+)
   #define MOTOR1_DIR_PIN 10    // Direction signal (GPIO 20, DIR+)
   #define MOTOR1_ENABLE_PIN 12 // Enable/Disable motor driver (optional), (When set to None, physically connected to GND)

   // Define motor2 GPIO pins
   #define MOTOR2_STEP_PIN 5    // Step signal (GPIO 26, PUL+)
   #define MOTOR2_DIR_PIN 6     // Direction signal (GPIO 20, DIR+)
   #define MOTOR2_ENABLE_PIN 8  // Enable/Disable motor driver (optional), (When set to None, physically connected to GND)

#elif defined DM542T_NEW
   /* Minimum delay in microseconds between step pulses for Stepper motor*/
   #define MIN_STEP_DELAY 10
   // Define motor1 GPIO pins
   #define MOTOR1_STEP_PIN 9    // Step signal (GPIO 21, PUL+)
   #define MOTOR1_DIR_PIN 10    // Direction signal (GPIO 20, DIR+)
   #define MOTOR1_ENABLE_PIN 12 // Enable/Disable motor driver (optional), (When set to None, physically connected to GND)

   // Define motor2 GPIO pins
   #define MOTOR2_STEP_PIN 5    // Step signal (GPIO 26, PUL+)
   #define MOTOR2_DIR_PIN 6     // Direction signal (GPIO 20, DIR+)
   #define MOTOR2_ENABLE_PIN 8  // Enable/Disable motor driver (optional), (When set to None, physically connected to GND)

   //library
   #include <AccelStepper.h>
   
   //Create instances of the AccelStepper class
   AccelStepper motor1(1, MOTOR1_STEP_PIN, MOTOR1_DIR_PIN);
   AccelStepper motor2(1, MOTOR2_STEP_PIN, MOTOR2_DIR_PIN);
   



#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);