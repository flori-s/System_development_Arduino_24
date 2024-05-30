/**
  * @author https://projecthub.arduino.cc/arduino_uno_guy/i2c-liquid-crystal-displays-5eb615
  * @author CHATGPT
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Pin voor knop 1
const int button1Pin = 8;   
// Pin voor knop 2
const int button2Pin = 12; 
// I2C address, aantal colummen, aantal rijen
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// Variabele om starttime in op te slaan
unsigned long startTime = 0;
// Variabele om vorige stopwatch tijd in op te slaan
unsigned long previousElapsedTime = 0;
// Variabele om op te slaan wanneer knop 1 voor het eerst was ingedrukt
unsigned long button1PressTime = 0;    
// Variabele om op de slaan of de stopwatch aan het lopen is of niet
bool isRunning = false;
// Variabele om op de slaan welke tijd de kop is ingedrukt
unsigned long buttonPressedTime = 0; 

void setup() {
  // PinMode defineren
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // LCD initializeren
  lcd.init();
  // Baclight aan doen
  lcd.backlight();
  // Curser op rij 1 zetten
  lcd.setCursor(0, 0);
  // Time formaat printen
  lcd.print("00:00:00.000");
  // Timer starten
  startTime = millis(); 
}

void loop() {
  // Button status ophalen als boolean
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // Chekcken of knop 1 is ingedrukt
  if (button1State == HIGH) {
    // Als de druk tijd nog niet is op geslaan
    if (button1PressTime == 0) { 
      // Op nemen wanneer de knop voor het eerst word ingedrukt
      button1PressTime = millis(); 
      // Check of de kn op 2 seconden of langer word ingedrukt
    } else if (millis() - button1PressTime >= 2000) { 
      // Lap laten zien
      displayLap();
      // Knop tijd ressetten 
      button1PressTime = 0; 
    }
    if (!isRunning) {
      // Start de stopwatch
      isRunning = true; 
      // Record de start tijd
      startTime = millis(); 
      // Vertraging voor een betere UX
      delay(100); 
    }
  } else {
    // Al de knop loslaat tijd ressetten
    button1PressTime = 0; 
  }

  // Check of knop 2 ingedrukt is om de stopwatch te ressetten 
  if (button2State == HIGH) {
    isRunning = false;
  }

  // Vertraging om de arduino tijd te geven om te checken of er op twee knoppen word gedrukt 
  delay(100);
    
  // Check of er op twee knoppen tegelijk word gedrukt
  if (button1State && button2State) {
    // LCD leeg maken
    lcd.clear();
    // Cursor op rij 1 zetten
    lcd.setCursor(0, 0);
    // Tijd formaat printen
    lcd.print("00:00:00.000");
  }

  // Scherm updaten alleen als de stopwatch loopt
  if (isRunning) {
    displayTime();
  }
}

void displayTime() {
  unsigned long currentTime = millis() - startTime;
  // Milliseconds ophalen
  unsigned long milliseconds = currentTime % 1000; 
  // Total seconden uitrekenen
  unsigned long seconds = currentTime / 1000;
  // Minuten uitrekenen
  unsigned long minutes = seconds / 60;
  // Uren uitrekenen
  unsigned long hours = minutes / 60;

  // Seconden, minuten en uren aanpassen om binnen range te blijven
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  // Print de tijd in "00:00:00.000" formaat
  lcd.setCursor(0, 0);
  lcd.print(hours < 10 ? "0" : "");
  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes < 10 ? "0" : "");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds < 10 ? "0" : "");
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(milliseconds < 100 ? "0" : ""); 
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}

void displayLap(){
  // voorbijgaande tijd uitrekenen
  unsigned long currentTime = (millis() - 2000) - startTime; 
  // Milliseconds ophalen
  unsigned long milliseconds = currentTime % 1000; 
  // Total seconden uitrekenen
  unsigned long seconds = currentTime / 1000; 
  // Minuten uitrekenen
  unsigned long minutes = seconds / 60; 
  // Uren uitrekenen
  unsigned long hours = minutes / 60; 

  // Seconden en minuten aanpassen om binnen range te blijven
  seconds %= 60;
  minutes %= 60;

  // Voorbijgaande tijd uitprinten in "00:00:00.000" formaat
  lcd.setCursor(0, 1);
  lcd.print(hours < 10 ? "0" : "");
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) lcd.print("0"); 
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0"); 
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(milliseconds < 100 ? "0" : ""); 
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}
