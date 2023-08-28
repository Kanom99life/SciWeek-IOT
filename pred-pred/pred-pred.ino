#include <Servo.h>
const int patternLength = 4;
Servo myservo;


void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(5);   // Turn servo back to 5 degrees
}

void loop() {
  if (Serial.available()) {
    char receivedChar = Serial.read();
    
    if (receivedChar == 'P') {  // Start of pattern data
      int patternArray[patternLength];
      for (int i = 0; i < patternLength; i++) {
        patternArray[i] = Serial.parseInt();
      }
      
      // Read the next 'U' indicating the start of userPattern data
      while (Serial.read() != 'U');

      int userPatternArray[patternLength];
      for (int i = 0; i < patternLength; i++) {
        userPatternArray[i] = Serial.parseInt();
      }

      // Compare patterns
      bool patternsMatch = true;
      for (int i = 0; i < patternLength; i++) {
        if (patternArray[i] != userPatternArray[i]) {
          patternsMatch = false;
          break;
        }
      }

      // Control servo based on pattern match
      if (patternsMatch) {
        myservo.write(95);  // Turn servo to 95 degrees
        delay(20000);       // Wait for 10 seconds
        myservo.write(5);   // Turn servo back to 5 degrees
      }
    }
  }
}
