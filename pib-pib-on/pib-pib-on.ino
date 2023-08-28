#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
const int trigPin = 13;
int echoPin = 12;

// Define an array to hold the random delays
int delays[] = {10, 50, 100, 200};

// Variable to track the spookyLights() start time
unsigned long spookyStartTime = 0;

// Flag to control spookyLights()
boolean isSpooky = false;

void setup() {
  Serial.begin(9600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
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
      analogWrite(REDPIN, 0);
      analogWrite(GREENPIN, 0);
      analogWrite(BLUEPIN, 0);
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
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);

  int randomDelay = delays[random(4)];
  delay(randomDelay);

  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);

  randomDelay = delays[random(4)];
  delay(randomDelay);
}

void normalLights() {
  // Normal lights
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
}
