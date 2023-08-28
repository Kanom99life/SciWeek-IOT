#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
// Define button pins
const int buttonPins[] = { 2, 3, 4, 5 };
int buzzerPin = 12;
// Define LED pins
const int ledPins[] = { 6, 7, 8, 9 };

// Define LCD pins
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Define the pattern
const int patternLength = 4;
int pattern[patternLength];  // Declare an array to store the pattern


void setup() {
  randomSeed(analogRead(A0));
  lcd.begin();
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  waitForButtonPress();  // Wait for any button to be pressed
  generateRandomPattern(pattern, patternLength);

  displayPattern();

  int userPattern[patternLength] = { -1, -1, -1, -1 };  // Initialize user input
  int userInputIndex = 0;

  while (userInputIndex < patternLength) {
    for (int i = 0; i < patternLength; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {  // Button pressed when LOW due to pull-up resistor
        Serial.println(i);
        userPattern[userInputIndex] = i;
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        userInputIndex++;
        delay(100);  // Debounce delay
        while (digitalRead(buttonPins[i]) == LOW)
          ;  // Wait until the button is released
      }
    }
  }

  // Compare user input with pattern
  bool isPatternCorrect = true;
  for (int i = 0; i < patternLength; i++) {
    if (userPattern[i] != pattern[i]) {
      isPatternCorrect = false;
      break;
    }
  }

  // Display result on LCD
  lcd.clear();
  if (isPatternCorrect) {
    lcd.setCursor(2, 1);
    delay(200);
    lcd.print("Pattern Correct!");
    for (int i = 0; i < 2; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
    };    
    


  } else {
    lcd.setCursor(1, 1);
    delay(200);
    lcd.print("Pattern Incorrect!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      delay(500);
    };
  }

  Serial.println("Pattern:");
  for (int i = 0; i < patternLength; i++) {
    Serial.print(pattern[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println("UserPattern:");
  for (int i = 0; i < patternLength; i++) {
    Serial.print(userPattern[i]);
    Serial.print(" ");
  }
  Serial.println();

  delay(2000);
  lcd.clear();


}

void waitForButtonPress() {
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("Press To Start");
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        return;  // Exit the function when a button is pressed
      }
    }
  }
}

void displayPattern() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Remember The Pattern");
  delay(2000);
  lcd.clear();

  lcd.setCursor(8, 1);
  lcd.print("Ready");
  delay(2000);

  lcd.clear();
  lcd.setCursor(10, 1);
  lcd.print("3");
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(1000);

  lcd.clear();
  lcd.setCursor(10, 1);
  lcd.print("2");
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(1000);

  lcd.clear();
  lcd.setCursor(10, 1);
  lcd.print("1");
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Remember The Pattern");
  digitalWrite(buzzerPin, HIGH);
  delay(1200);
  digitalWrite(buzzerPin, LOW);
  delay(800);

  for (int i = 0; i < patternLength; i++) {
    digitalWrite(ledPins[pattern[i]], HIGH);
    delay(500);
    digitalWrite(ledPins[pattern[i]], LOW);
    delay(700);
  }

  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("Enter  Pattern");

  delay(100);
}

void generateRandomPattern(int patternArray[], int length) {
  for (int i = 0; i < length; i++) {
    patternArray[i] = random(0, 4);  // Generates a random number between 0 and 3
  }
}
