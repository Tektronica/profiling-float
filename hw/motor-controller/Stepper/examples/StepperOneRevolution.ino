/*
Stepper one revolution
Turn the shaft one revolution clockwise and one counterclockwise.
https://www.arduino.cc/reference/en/libraries/stepper/
*/

#include <Stepper.h>

// change this to fit the number of steps per revolution
const int stepsPerRevolution = 200; 

// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup()
{
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);

  // initialize the serial port:
  Serial.begin(9600);
}

void loop()
{
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
