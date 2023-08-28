#include <Servo.h>
Servo myservo;
int led1 = 11;

int startPos = 40;     // Starting position in degrees
int endPos = 180;     // Ending position in degrees
int stepSize = 1;     // Step size for smoother movement
int delayTime = 25;   // Delay time in milliseconds
unsigned long previousMillis = 0;  // To store the last time servo moved
unsigned long ledMillis = 0;       // To store the last time LED changed
const int ledInterval = 10;       // Interval for LED brightness change (milliseconds)
int brightness = 0;  // Current LED brightness
int brightnessStep = 1;  // Step size for changing brightness

void setup() {
  pinMode(led1, OUTPUT);
  myservo.attach(9);
}

void loop() {
  unsigned long currentMillis = millis();

  // Change LED brightness gradually
  if (currentMillis - ledMillis >= ledInterval) {
    ledMillis = currentMillis;
    analogWrite(led1, brightness);
    
    brightness += brightnessStep;
    if (brightness <= 0 || brightness >= 255) {
      brightnessStep = -brightnessStep; // Reverse brightness change direction at limits
    }
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
