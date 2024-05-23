#include <Servo.h>

// Pin for button 1
const int button1Pin = 3;  
// Pin for button 2 
const int button2Pin = 10; 
// Pin for the servo motor
const int servoPin = 12; 

Servo myServo;

void setup() {
  // setting pin mode
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // setting servo
  myServo.attach(servoPin);
}

void loop() {
  // getting button state as boolean
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // setting delay to give the arduino tim to check for a dubble click
  delay(200);

  // check dubble click
  if (button1State && button2State) {
    // move the servoc in 5s, wait 2s, then return in 0.5s
    moveServo(0, 120, 5000);
    delay(2000);
    moveServo(120, 0, 500);
  }
  // check if btn 1 is clicked
  else if (button1State) {
    // move servo in 5s, then return in 5s
    moveServo(0, 120, 5000);
    moveServo(120, 0, 5000);
  } 
  // check if btn 2 is clicked
  else if (button2State) {
    // move servo in 0.5s, then return in 0.5s
    moveServo(0, 120, 500);
    moveServo(120, 0, 500);
  }
}

// Function moveServo 
void moveServo(int startAngle, int endAngle, int duration) {
  // Calculate stepdelay
  int stepDelay = duration / abs(endAngle - startAngle);

 if (startAngle < endAngle) {
    // If the starting angle is less than the ending angle,
    // the servo needs to move from the start angle to the end angle in increasing order.
    for (int angle = startAngle; angle <= endAngle; angle++) {
        // Write the current angle value to the servo motor
        myServo.write(angle);
        // Wait for the specified delay time before moving to the next angle
        delay(stepDelay);
    }
} else {
    // If the starting angle is greater than or equal to the ending angle,
    // the servo needs to move from the start angle to the end angle in decreasing order.
    for (int angle = startAngle; angle >= endAngle; angle--) {
        // Write the current angle value to the servo motor
        myServo.write(angle);
        // Wait for the specified delay time before moving to the next angle
        delay(stepDelay);
    }
  }
}
