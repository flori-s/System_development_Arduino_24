void setup() {
  // Defining the pin numbers and mode.
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // Set pin 10 to high
  digitalWrite(10, HIGH);
  // Set delay of 1.5 s
  delay(1500);
  // Set pin 10 to low
  digitalWrite(10, LOW);
  // Set pin 13 to high
  digitalWrite(13, HIGH);
  // Set delay of 1.5 s
  delay(1500);
  // Set pin 13 to low
  digitalWrite(13, LOW);
}
