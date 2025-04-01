/***************************************************************
   Motor driver definitions

   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   *************************************************************/

#ifdef USE_BASE

#ifdef POLOLU_VNH5019
/* Include the Pololu library */
#include "DualVNH5019MotorShield.h"

/* Create the motor driver object */
DualVNH5019MotorShield drive;

/* Wrap the motor driver initialization */
void initMotorController()
{
  drive.init();
}

/* Wrap the drive motor set speed function */
void setMotorSpeed(int i, int spd)
{
  if (i == LEFT)
    drive.setM1Speed(spd);
  else
    drive.setM2Speed(spd);
}

// A convenience function for setting both motor speeds
void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#elif defined POLOLU_MC33926
/* Include the Pololu library */
#include "DualMC33926MotorShield.h"

/* Create the motor driver object */
DualMC33926MotorShield drive;

/* Wrap the motor driver initialization */
void initMotorController()
{
  drive.init();
}

/* Wrap the drive motor set speed function */
void setMotorSpeed(int i, int spd)
{
  if (i == LEFT)
    drive.setM1Speed(spd);
  else
    drive.setM2Speed(spd);
}

// A convenience function for setting both motor speeds
void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#elif defined L298_MOTOR_DRIVER
void initMotorController()
{
  digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
  digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
}

void setMotorSpeed(int i, int spd)
{
  unsigned char reverse = 0;

  if (spd < 0)
  {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255)
    spd = 255;

  if (i == LEFT)
  {
    if (reverse == 0)
    {
      analogWrite(LEFT_MOTOR_FORWARD, spd);
      analogWrite(LEFT_MOTOR_BACKWARD, 0);
    }
    else if (reverse == 1)
    {
      analogWrite(LEFT_MOTOR_BACKWARD, spd);
      analogWrite(LEFT_MOTOR_FORWARD, 0);
    }
  }
  else /*if (i == RIGHT) //no need for condition*/
  {
    if (reverse == 0)
    {
      analogWrite(RIGHT_MOTOR_FORWARD, spd);
      analogWrite(RIGHT_MOTOR_BACKWARD, 0);
    }
    else if (reverse == 1)
    {
      analogWrite(RIGHT_MOTOR_BACKWARD, spd);
      analogWrite(RIGHT_MOTOR_FORWARD, 0);
    }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}

#elif defined DM542T
// Init motor controller
void initMotorController()
{
  // Set all stepper motor pins as output
  pinMode(MOTOR1_STEP_PIN, OUTPUT);
  pinMode(MOTOR1_DIR_PIN, OUTPUT);
  pinMode(MOTOR1_ENABLE_PIN, OUTPUT);

  pinMode(MOTOR2_STEP_PIN, OUTPUT);
  pinMode(MOTOR2_DIR_PIN, OUTPUT);
  pinMode(MOTOR2_ENABLE_PIN, OUTPUT);

  // Enable the motors (DM542T typically uses LOW to enable)
  digitalWrite(MOTOR1_ENABLE_PIN, LOW);
  digitalWrite(MOTOR2_ENABLE_PIN, LOW);
}

// Set the speed and direction for a single motor
void setMotorSpeed(int motor, int speed)
{
  unsigned long pulse_delay; // Time between pulses for stepper motors
  bool direction;

  // Map speed to a delay (lower delay =  higher speed)
  pulse_delay = map(abs(speed), 0, 255, 2000, MIN_STEP_DELAY);

  // Determine direction based on the sign of speed
  direction = (speed >= 0) ? HIGH : LOW;
  if (motor == LEFT)
  {
    digitalWrite(MOTOR1_DIR_PIN, direction); // Set direction
    for (int i = 0; i < abs(speed); i++)
    {
      digitalWrite(MOTOR1_STEP_PIN, HIGH); // Step signal
      digitalMicroseconds(pulse_delay);    // Wait
      digitalWrite(MOTOR1_STEP_PIN, LOW)   // End step
          delayMicroseconds(pulse_delay);  // Wait
    }
  }
  else if (motor == RIGHT)
  {
    digitalWrite(MOTOR2_DIR_PIN, direction); // Set direction
    for (int i = 0; i < abs(speed); i++)
    {
      digitalWrite(MOTOR2_STEP_PIN, HIGH); // Step signal
      digitalMicroseconds(pulse_delay);    // Wait
      digitalWrite(MOTOR2_STEP_PIN, LOW);  // End step
      delayMicroseconds(pulse_delay);      // Wait
    }
  }
}

// Set speeds for both motors
void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}

#elif defined DM542T_NEW
void initMotorController()
{
  // motor
  motor1.setMaxSpeed(1000.0);
  motor1.setAcceleration(500.0);

  motor2.setMaxSpeed(1000.0);
  motor2.setAcceleration(500.0);
}

void setMotorSpeed(int motor, int speed)
{
  bool direction;
  long mappedSpeed = 0;
  // Map PWM speed to stepper speed
  mappedSpeed = map(abs(speed), 0, 255, 0, 1000);
  if (speed < 0)
  {
    mappedSpeed *= -1;
  }
  // Determine which motor
  if (motor == LEFT)
  {
    motor1.setSpeed(mappedSpeed);
  } else if (motor == RIGHT) {
    motor2.setSpeed(-mappedSpeed);
  }
}
// Set speeds for both motors
void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}

#else
#error A motor driver must be selected!
#endif

#endif