// Array maken voor alle pinnen
const int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9};    

void setup() {
  // pinMode defineren door middel van een loop
  for (int count = 0; count < 8; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  // De knightrider methode aanroepen met 80 als parameter
  knightrider(80);
}

void knightrider(int dTime) {
  // Rechts naar links
  for (int i = 0; i < 8; i++) {
    // Zet pin op HIGH
    digitalWrite(pinArray[i], HIGH);
    // Vertraging 80 ms
    delay(dTime);
    // Vorige led uit doen voor een mooie transitie
    if (i > 0) {  
      digitalWrite(pinArray[i - 1], LOW);
    }
  }
  // Laatste led uit doen voor een vloeiendere transitie
  digitalWrite(pinArray[7], LOW); 

  // Links naar rechts
  for (int i = 7; i >= 0; i--) {
    // Zet pin op HIGH
    digitalWrite(pinArray[i], HIGH);
    // Vertraging 80 ms
    delay(dTime);
    // Vorige led uit doen voor een mooie transitie
    if (i < 7) {  
      digitalWrite(pinArray[i + 1], LOW);
    }
  }
  // Laatste led uit doen voor een vloeiendere transitie
  digitalWrite(pinArray[0], LOW); 
}
