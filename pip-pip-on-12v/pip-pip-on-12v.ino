#include <FastLED.h>

#define NUM_LEDS 144  // Change this to the number of LEDs in your strip
#define DATA_PIN 7    // Change this to the data pin connected to the LED strip
const int trigPin = 13;
const int echoPin = 12;

CRGB leds[NUM_LEDS];
// Define an array to hold the random delays
int delays[] = {10, 50, 100, 200};

// Variable to track the spookyLights() start time
unsigned long spookyStartTime = 0;

// Flag to control spookyLights()
boolean isSpooky = false;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, BRG>(leds, NUM_LEDS);
  FastLED.show();
}

void loop() {
  long distance = getUltrasonicDistance();

  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(100);

  if (distance <= 60) {
    spookyStartTime = millis();
    isSpooky = true; // Set the spooky flag
  }

  if (isSpooky) {
    spookyLights();
    // Check if 5 seconds have passed since spookyLights() started
    if (millis() - spookyStartTime >= 2000) {
      isSpooky = false; // Reset the spooky flag
      // Turn off spooky lights after 5 seconds      
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
    }
  } else {
    normalLights();
  }
}

long getUltrasonicDistance() {
  long duration, cm;
  pinMode(trigPin, OUTPUT);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = duration* 0.0343 / 2; 
  return cm;
}

void spookyLights() {
  // Spooky lights and delays
  // Fill the strip with a color (red in this case)
  fill_solid(leds, NUM_LEDS, CRGB::Red);  // This is actually sending GRB data
  FastLED.show();

  int randomDelay = delays[random(4)];
  delay(randomDelay);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  randomDelay = delays[random(4)];
  delay(randomDelay);
}

void normalLights() {
  // Normal lights
  // Fill the strip with a color (red in this case)
  fill_solid(leds, NUM_LEDS, CRGB::Red);  // This is actually sending GRB data
  FastLED.show();
}