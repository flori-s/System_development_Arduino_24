// Alle pinnen defineren
int btnPin = 6;
int ledPin1 = 8;
int ledPin2 = 13;

// Variabelen defineren
int buttonState = 0;        
int lastButtonState = 0;     
int counter = 0; 

void setup(){
  // pinMode defineren
  pinMode(btnPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // De btn methode aanroepen met 50 als parameter
  btn(50);
}

void btn(int dTime){
  // Btn state ophalen
  buttonState = digitalRead(btnPin); 

  // Check of de buttonstate is veranderd 
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // Counter + 1
      counter++;
      
      // LED updaten gebasseerd op de counter value
      // The Counter start bij 0 dus na de eerste druk is de counter 1 dit triggered de else. Na de tweede druk is de counter 2 dit komt overeen met de if statement. 
      if (counter % 2 == 0) {
        // Doe LED 1 uit
        digitalWrite(ledPin1, LOW);  
        // Doe LED 2 aan
        digitalWrite(ledPin2, HIGH); 
      } else {
        // Doe LED 1 aan
        digitalWrite(ledPin1, HIGH); 
        // Doe LED 2 uit
        digitalWrite(ledPin2, LOW);  
      }
      // Vertraging 
      delay(dTime);
    }
  }
  // Sla de cuurent state op als de laatste state 
  lastButtonState = buttonState; 
}
