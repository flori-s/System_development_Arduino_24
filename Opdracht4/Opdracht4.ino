const int pinArray[] = {3, 5, 7, 8, 10, 12};
const int PinPotentiometer = A5;
const int numLeds = 6;

void setup() {
  for (int count = 0; count < 6; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
  pinMode(PinPotentiometer, INPUT);
}

void loop(){
  int sensorValue = analogRead(PinPotentiometer);
  int ledThreshold = map(sensorValue, 0, 1023, numLeds, 0);

    // Control the LEDs based on the potentiometer value
  for (int i = 0; i < numLeds; i++) {
    if (i < ledThreshold) {
      digitalWrite(pinArray[i], LOW); // Turn on LED
    } else {
      digitalWrite(pinArray[i], HIGH);  // Turn off LED
    }
  }

  delay(50); // Small delay to stabilize the reading
}
