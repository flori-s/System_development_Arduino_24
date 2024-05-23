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
    // set pin High
    digitalWrite(pinArray[i], HIGH);
    // delay 80 ms
    delay(dTime);
    // Turn off the previous LED for a smooth transition
    if (i > 0) {  
      digitalWrite(pinArray[i - 1], LOW);
    }
  }
  // Turn off the last LED after the loop for a smooth transition
  digitalWrite(pinArray[7], LOW); 

  // Move left to right
  for (int i = 7; i >= 0; i--) {
    // set pin High
    digitalWrite(pinArray[i], HIGH);
    // delay 80 ms
    delay(dTime);
    // Turn off the previous LED for a smooth transition
    if (i < 7) {  
      digitalWrite(pinArray[i + 1], LOW);
    }
  }
  // Turn off the last LED after the loop for a smooth transition
  digitalWrite(pinArray[0], LOW); 
}
