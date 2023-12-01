int led = 3;         // the PWM pin the LED is attached to
int fadeSteps = 5;    // the number of steps for the fade (adjust for smoother fade)
int minFadeDelay = 30; // minimum delay time between steps
int maxFadeDelay = 70; // maximum delay time between steps
int minWaitTime = 200; // minimum wait time between flickers
int maxWaitTime = 500; // maximum wait time between flickers
int brightness = 0;
int bn = 0;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin A0 to be an output:
  pinMode(led, OUTPUT);
}

// function to generate a random value within a range
int randomRange(int minVal, int maxVal) {
  return minVal + random(maxVal - minVal + 1);
}

// the loop routine runs over and over again forever:
void loop() {
  // Fade In
  for (int brightness = bn; brightness <= 255; brightness += randomRange(1, fadeSteps)) {
    delay(randomRange(minFadeDelay, maxFadeDelay));
    analogWrite(led, brightness);
    bn = brightness;
  }
  delay(randomRange(minWaitTime, maxWaitTime));

  // Fade Out
  for (brightness = bn; brightness >= 5; brightness -= randomRange(1, fadeSteps)) {
    analogWrite(led, brightness);
    delay(randomRange(minFadeDelay, maxFadeDelay));
    bn = brightness;
  }
  delay(randomRange(minWaitTime, maxWaitTime));

  // Fade In
  for (brightness = bn; brightness <= 255; brightness += randomRange(1, fadeSteps)) {
    delay(randomRange(minFadeDelay, maxFadeDelay));
    analogWrite(led, brightness);
    bn = brightness;
  }
  delay(randomRange(minWaitTime, maxWaitTime));

  // Fade Out
  for (brightness = bn; brightness >= 10; brightness -= randomRange(1, fadeSteps)) {
    analogWrite(led, brightness);
    delay(randomRange(minFadeDelay, maxFadeDelay));
    bn = brightness;
  }
  delay(randomRange(minWaitTime, maxWaitTime));
}
