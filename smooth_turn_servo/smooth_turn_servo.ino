#include <Servo.h>
Servo myservo;
int led1 = 12;
int led2 = 13;
int startPos = 40;     // Starting position in degrees
int endPos = 180;     // Ending position in degrees
int stepSize = 1;     // Step size for smoother movement
int delayTime = 25;   // Delay time in milliseconds
unsigned long previousMillis = 0;  // To store the last time servo moved
unsigned long ledMillis = 0;       // To store the last time LED blinked
const int ledInterval = 3000;       // Interval for LED blinking (milliseconds)

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  myservo.attach(9);
}

void loop() {
  unsigned long currentMillis = millis();

  // Blink LEDs every 500 milliseconds
  if (currentMillis - ledMillis >= ledInterval) {
    ledMillis = currentMillis;
    digitalWrite(led1, !digitalRead(led1)); // Toggle LED state
    digitalWrite(led2, !digitalRead(led2)); // Toggle LED state
  }

  // Move servo with a delay
  if (currentMillis - previousMillis >= delayTime) {
    previousMillis = currentMillis;

    if (myservo.read() <= startPos || myservo.read() >= endPos) {
      stepSize = -stepSize; // Reverse step direction at limits
    }

    myservo.write(myservo.read() + stepSize);
  }
}
