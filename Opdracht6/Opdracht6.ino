#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Pin for button 1
const int button1Pin = 8;   
// Pin for button 2
const int button2Pin = 12; 
// I2C address, number of columns, number of rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// Variable to store the starttime 
unsigned long startTime = 0;
// Variable to store the time of the previous stopwatch
unsigned long previousElapsedTime = 0;
// Variable to store when button1 was first pressed
unsigned long button1PressTime = 0;    
// Variable to store if the stopwatch is running or not
bool isRunning = false;
// Variable to store the time when the button is pressed
unsigned long buttonPressedTime = 0; 

void setup() {
  // setting pin mode
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // initiate LCD
  lcd.init();
  // Turn on backlight
  lcd.backlight();
  // set cursor to first row
  lcd.setCursor(0, 0);
  // print time format
  lcd.print("00:00:00.000");
  // Start the timer
  startTime = millis(); 
}

void loop() {
  // get button state as boolean
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // Check if button 1 is pressed
  if (button1State == HIGH) {
    // If button press time is not recorded yet
    if (button1PressTime == 0) { 
      // Record the time when button is first pressed
      button1PressTime = millis(); 
      // Check if button is pressed for 2 seconds or more
    } else if (millis() - button1PressTime >= 2000) { 
      // Show lap
      displayLap();
      // Reset the button press time
      button1PressTime = 0; 
    }
    if (!isRunning) {
      // Start the stopwatch
      isRunning = true; 
      // Record the start time
      startTime = millis(); 
      // Delay to debounce the button
      delay(100); 
    }
  } else {
    // Reset button press time when button is released
    button1PressTime = 0; 
  }

  // Check if button 2 is pressed to reset the stopwatch
  if (button2State == HIGH) {
    isRunning = false;
  }

  // delay to give the arduino tim to check for a dubble click
  delay(100);
    
  // check for a dubble click
  if (button1State && button2State) {
    // clear the lcd
    lcd.clear();
    // set cursor to teh first row
    lcd.setCursor(0, 0);
    // print time format
    lcd.print("00:00:00.000");
  }

  // Update the display only if the stopwatch is running
  if (isRunning) {
    displayTime();
  }
}

void displayTime() {
  unsigned long currentTime = millis() - startTime;
  // Extract milliseconds
  unsigned long milliseconds = currentTime % 1000; 
  // Calculate total seconds
  unsigned long seconds = currentTime / 1000;
  // Calculate minutes
  unsigned long minutes = seconds / 60;
  // Calculate hours
  unsigned long hours = minutes / 60;

  // Adjust seconds, minutes and hours to remain within the range
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  // Print the time in "00:00:00.000" format
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
  // Print leading zeros for milliseconds
  lcd.print(milliseconds < 100 ? "0" : ""); 
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}

void displayLap(){
  // Calculate elapsed time
  unsigned long currentTime = (millis() - 2000) - startTime; 
  // Extract milliseconds
  unsigned long milliseconds = currentTime % 1000; 
  // Calculate total seconds
  unsigned long seconds = currentTime / 1000; 
  // Calculate minutes
  unsigned long minutes = seconds / 60; 
  // Calculate hours
  unsigned long hours = minutes / 60; 

  // Adjust seconds and minutes to remain within the range
  seconds %= 60;
  minutes %= 60;

  // Print the elapsed time in "00:00:00.000" format
  lcd.setCursor(0, 1);
  lcd.print(hours < 10 ? "0" : "");
  lcd.print(hours);
  lcd.print(":");
  // Ensure two digits for minutes
  if (minutes < 10) lcd.print("0"); 
  lcd.print(minutes);
  lcd.print(":");
  // Ensure two digits for seconds
  if (seconds < 10) lcd.print("0"); 
  lcd.print(seconds);
  lcd.print(".");
  // Print leading zeros for milliseconds
  lcd.print(milliseconds < 100 ? "0" : ""); 
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}
