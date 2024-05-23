// Defining the pin's
int btnPin = 6;
int ledPin1 = 8;
int ledPin2 = 13;

// Defining the variables
int buttonState = 0;        
int lastButtonState = 0;     
int counter = 0; 

void setup(){
  // pinMode setup
  pinMode(btnPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // Calling the btn method with 50 as parameter
  btn(50);
}

void btn(int dTime){
  // Get btn state
  buttonState = digitalRead(btnPin); 

  // Check if the buttonstate has changed
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // Counter + 1
      counter++;
      
      // Update LED states based on counter value
      // The Counter starts at 0 so after the first push the counter is 1 which will trigger the else. After the second push the counter is 2 which meets the if statement. 
      if (counter % 2 == 0) {
        // Turn off LED 1
        digitalWrite(ledPin1, LOW);  
        // Turn on LED 2
        digitalWrite(ledPin2, HIGH); 
      } else {
        // Turn on LED 1
        digitalWrite(ledPin1, HIGH); 
        // Turn off LED 2
        digitalWrite(ledPin2, LOW);  
      }
      // Delay for debouncing
      delay(dTime);
    }
  }
  // Save the current state as the last state
  lastButtonState = buttonState; 
}
