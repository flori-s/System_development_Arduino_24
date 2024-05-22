// Create array for the pin's
const int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9};    

void setup() {
  // pinMode setup using loop
  for (int count = 0; count < 8; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  // Calling the btn method with 80 as parameter
  knightrider(80);
}

void knightrider(int dTime) {
  // Move right to left
  for (int i = 0; i < 8; i++) {
    digitalWrite(pinArray[i], HIGH);
    delay(dTime);
    if (i > 0) {  // Turn off the previous LED
      digitalWrite(pinArray[i - 1], LOW);
    }
  }
  digitalWrite(pinArray[7], LOW); // Turn off the last LED after the loop

  // Move left to right
  for (int i = 7; i >= 0; i--) {
    digitalWrite(pinArray[i], HIGH);
    delay(dTime);
    if (i < 7) {  // Turn off the previous LED
      digitalWrite(pinArray[i + 1], LOW);
    }
  }
  digitalWrite(pinArray[0], LOW); // Turn off the first LED after the loop
}
