void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, HIGH);
  delay(1500);
  digitalWrite(10, LOW);
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(13, LOW);
}
