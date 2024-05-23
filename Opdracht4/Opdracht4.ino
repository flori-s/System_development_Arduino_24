// Creating pin array for the pins needed
int pinArray[] = {3, 5, 7, 8, 10, 12};
// Giving the input a analog pin
int PinPotentiometer = A5;
// setting the number of leds
int numLeds = 6;

void setup() {
  // setting up pin mode for every pin in the array using a loop
  for (int count = 0; count < 6; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
  // setting up pin mode for the analog input
  pinMode(PinPotentiometer, INPUT);
}

void loop(){
  //calling method
  reactOnInput(50);
}

void reactOnInput(int dTime){
  // getting the sesonr value
  int sensorValue = analogRead(PinPotentiometer);
  // mapping the potentiometer with the sensorvalue, 
  // minimum sensorvalue, maximum sensorvalue, maximum mapped value, minimum mapped value 
  int ledThreshold = map(sensorValue, 0, 1023, numLeds, 0);

  // Control the LEDs based on the potentiometer value
  for (int i = 0; i < numLeds; i++) {
    if (i < ledThreshold) {
      // Turn on LED
      digitalWrite(pinArray[i], LOW); 
    } else {
      // Turn off LED
      digitalWrite(pinArray[i], HIGH);  
    }
  }
  
  // Small delay to stabilize the reading
  delay(dTime); 
}