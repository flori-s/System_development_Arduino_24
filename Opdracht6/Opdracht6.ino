#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int button1Pin = 8;   // Pin for button 1
const int button2Pin = 12; 
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, number of columns, number of rows
unsigned long startTime = 0;
unsigned long previousElapsedTime = 0; // Variable to store the time of the previous stopwatch
unsigned long button1PressTime = 0;    // Variable to store when button1 was first pressed

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("00:00:00.000"); // Initialize the display with milliseconds
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  startTime = millis(); // Start the timer
}

bool isRunning = false;

unsigned long buttonPressedTime = 0; // Variable to store the time when the button is pressed

void loop() {
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // Check if button 1 is pressed
  if (button1State == HIGH) {
    if (button1PressTime == 0) { // If button press time is not recorded yet
      button1PressTime = millis(); // Record the time when button is first pressed
    } else if (millis() - button1PressTime >= 2000) { // Check if button is pressed for 2 seconds or more
      displayLap();
      button1PressTime = 0; // Reset the button press time
    }
    if (!isRunning) {
        isRunning = true; // Start the stopwatch
        startTime = millis(); // Record the start time
        delay(100); // Delay to debounce the button
    }
  } else {
    button1PressTime = 0; // Reset button press time when button is released
  }

  // Check if button 2 is pressed to reset the stopwatch
  if (button2State == HIGH) {
    isRunning = false;
  }

  delay(100);
  if (button1State && button2State) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("00:00:00.000");
  }

  // Update the display only if the stopwatch is running
  if (isRunning) {
    displayTime();
  }
}

void displayTime() {
  unsigned long currentTime = millis() - startTime;
  unsigned long milliseconds = currentTime % 1000; // Extract milliseconds
  unsigned long seconds = currentTime / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  seconds %= 60;
  minutes %= 60;
  hours %= 24;

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
  lcd.print(milliseconds < 100 ? "0" : ""); // Print leading zeros for milliseconds
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}

void displayLap(){
  unsigned long currentTime = (millis() - 2000) - startTime; // Calculate elapsed time
  unsigned long milliseconds = currentTime % 1000; // Extract milliseconds
  unsigned long seconds = currentTime / 1000; // Calculate total seconds
  unsigned long minutes = seconds / 60; // Calculate minutes
  unsigned long hours = minutes / 60; // Calculate hours

  // Adjust seconds and minutes to remain within the range
  seconds %= 60;
  minutes %= 60;

  // Print the elapsed time in "00:00:00.000" format
  lcd.setCursor(0, 1);
  lcd.print(hours < 10 ? "0" : "");
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) lcd.print("0"); // Ensure two digits for minutes
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0"); // Ensure two digits for seconds
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(milliseconds < 100 ? "0" : ""); // Print leading zeros for milliseconds
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}
