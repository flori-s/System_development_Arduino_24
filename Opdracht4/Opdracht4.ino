/**
  * @author https://forum.arduino.cc/t/help-with-analog-input/379975
  * @author CHATGPT
*/

// Een pin array aanmaken voor alle pinnen
int pinArray[] = {3, 5, 7, 8, 10, 12};
// De pin aan een analoge pin koppelen
int PinPotentiometer = A5;
// Het aantal leds defineren
int numLeds = 6;

void setup() {
  // Alle pinModes defineren voor de pins in de array  
  for (int count = 0; count < 6; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
  // De pinMode defineren voor de anologe pin
  pinMode(PinPotentiometer, INPUT);
}

void loop(){
  // Methode aanroepn met 50 als parameter
  reactOnInput(50);
}

void reactOnInput(int dTime){
  // De sensor waarde ophalen
  int sensorValue = analogRead(PinPotentiometer);
  // De potentiemeter mappen met de sensorvalue, 
  // minimum sensorvalue, maximum sensorvalue, maximum mapped value, minimum mapped value 
  int ledThreshold = map(sensorValue, 0, 1023, numLeds, 0);

  // De leds aansturen gebasseerd op de sensorvalue
  for (int i = 0; i < numLeds; i++) {
    if (i < ledThreshold) {
      // Doe led aan
      digitalWrite(pinArray[i], LOW); 
    } else {
      // Doe led uit
      digitalWrite(pinArray[i], HIGH);  
    }
  }
  
  // Een delay om het duidelijker te maken
  delay(dTime); 
}