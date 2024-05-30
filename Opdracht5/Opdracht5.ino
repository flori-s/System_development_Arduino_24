/**
  * @author https://docs.arduino.cc/learn/electronics/servo-motors/
  * @author CHATGPT
*/

#include <Servo.h>

// Pin voor knop 1
const int button1Pin = 3;  
// Pin voor knop 2 
const int button2Pin = 10; 
// Pin voor de servo motor
const int servoPin = 12; 

Servo myServo;

void setup() {
  // De pinMode defineren
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // De servo defineren
  myServo.attach(servoPin);
}

void loop() {
  // De button state ophalen als boolean
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // Een vertraging om de arduino tijd te geven om te checken of er twee knoppen worden ingedrukt
  delay(200);

  // Checken of er twee knoppen worden ingedrukt
  if (button1State && button2State) {
    // Verplaats the servo in 5s, wacht 2s, daarna terug in 0.5s
    moveServo(0, 120, 5000);
    delay(2000);
    moveServo(120, 0, 500);
  }
  // Checken of knop 1 word ingedrukt
  else if (button1State) {
    // Verplaats servo in 5s, daarna terug in 5s
    moveServo(0, 120, 5000);
    moveServo(120, 0, 5000);
  } 
  // Checken of knop 2 word ingedrukt
  else if (button2State) {
    // Verplaats servo in 0.5s, daarna terug in 0.5s
    moveServo(0, 120, 500);
    moveServo(120, 0, 500);
  }
}

// Functie moveServo 
void moveServo(int startAngle, int endAngle, int duration) {
  // Stepdelay berekenen
  int stepDelay = duration / abs(endAngle - startAngle);

 if (startAngle < endAngle) {
    // Als de start angle minder is dan het eind angle,
    // de servo word verplaats van de start angle naar de eind angle in een versnellende beweging.
    for (int angle = startAngle; angle <= endAngle; angle++) {
        // De huidige angle aan de servo doorgeven
        myServo.write(angle);
        // Wachten op de stepdelay voor dat hij door gaat
        delay(stepDelay);
    }
} else {
    // Als de start angel groter of gelijk is aan de eind angle,
    // de servo moet worden verplaats van start angle naar eind angle in een verminderende beweging.
    for (int angle = startAngle; angle >= endAngle; angle--) {
        // De huidige angle aan de servo doorgeven
        myServo.write(angle);
        // Wachten op de stepdelay voor dat hij door gaat
        delay(stepDelay);
    }
  }
}
