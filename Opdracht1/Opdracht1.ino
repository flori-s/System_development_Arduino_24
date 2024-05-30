void setup() {
  // De pin nummers defineren
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // Pin 10 op HIGH zetten
  digitalWrite(10, HIGH);
  // Vertraging van 1.5 s
  delay(1500);
  // Pin 10 op LOW zetten
  digitalWrite(10, LOW);
  // Pin 13 op HIGH zetten
  digitalWrite(13, HIGH);
  // Vertraging van 1.5 s
  delay(1500);
  // Pin 13 op LOW zetten
  digitalWrite(13, LOW);
}
