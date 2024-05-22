#include <Servo.h>

const int button1Pin = 3;   // Pin for button 1
const int button2Pin = 10;   // Pin for button 2
const int servoPin = 12;     // Pin for the servo motor

Servo myServo;

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  myServo.attach(servoPin);
}

void loop() {
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  delay(200);
  if (button1State && button2State) {
    moveServo(0, 120, 5000);
    delay(2000);
    moveServo(120, 0, 500);
  }
  else if (button1State) {
    // Only button 1 pressed: move servo in 5s, then return in 5s
    moveServo(0, 120, 5000);
    moveServo(120, 0, 5000);
  } else if (button2State) {
    // Only button 2 pressed: move servo in 0.5s, then return in 0.5s
    moveServo(0, 120, 500);
    moveServo(120, 0, 500);
  }
}
void moveServo(int startAngle, int endAngle, int duration) {
  int stepDelay = duration / abs(endAngle - startAngle);

  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      myServo.write(angle);
      delay(stepDelay);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      myServo.write(angle);
      delay(stepDelay);
    }
  }
}
