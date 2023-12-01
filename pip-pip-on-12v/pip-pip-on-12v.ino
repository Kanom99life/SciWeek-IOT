#include <FastLED.h>

#define NUM_LEDS 144  // Change this to the number of LEDs in your strip
#define DATA_PIN 7    // Change this to the data pin connected to the LED strip
#define BRIGHTNESS 32 // Change this value to adjust brightness (0-255)

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, BRG>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS); // Set the initial brightness
  FastLED.show();
}

void loop() {
  normalLights();
}

void normalLights() {
  // fill_solid(leds, NUM_LEDS, CRGB(50, 202, 241)); //blue
  // fill_solid(leds, NUM_LEDS, CRGB(8, 232, 222)); //blue

  // fill_solid(leds, NUM_LEDS, CRGB(175, 238, 238)); //light_blue
  // fill_solid(leds, NUM_LEDS, CRGB(64, 224, 208)); //light_blue
  
  fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0)); //warm_light
  // fill_solid(leds, NUM_LEDS, CRGB(255, 80, 5)); //warm_light
  // fill_solid(leds, NUM_LEDS, CRGB(255, 90, 5)); //warm_light
  FastLED.show();
}
