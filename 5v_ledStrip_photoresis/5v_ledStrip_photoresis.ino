#define BLUEPIN 3
#define REDPIN 5
#define GREENPIN 6
int ldrpin1 = A0;
int ldrpin2 = A1;
int ldrpin3 = A2;

int brightness;
int fadeSteps = 5; 
int fadeDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(ldrpin1, INPUT);
  pinMode(ldrpin2, INPUT);
  pinMode(ldrpin3, INPUT);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
}

void loop() {
  int ldrValue1 = analogRead(ldrpin1);
  int ldrValue2 = analogRead(ldrpin2);
  int ldrValue3 = analogRead(ldrpin3);
  Serial.print("LDR1 : ");
  Serial.println(ldrValue1);
  // delay(50);
  Serial.print("LDR2 : ");
  Serial.println(ldrValue2);
  // delay(50);
  Serial.print("LDR3 : ");
  Serial.println(ldrValue3);
  // delay(500);
  int ldr_avg = (ldrValue1 + ldrValue2 + ldrValue3) / 3; // ldr average

  if (ldr_avg > 500) {
    // Fade In
    for (int brightness = 0; brightness <= 255; brightness += fadeSteps) {
      delay(fadeDelay);
      analogWrite(REDPIN, brightness);      
    }
    delay(100);
  } else {
    // Fade Out
    for (brightness = 255; brightness >= 0; brightness -= fadeSteps) {
      analogWrite(REDPIN, brightness);
      delay(fadeDelay);
    }
    delay(100);
  }
  delay(1000);
  
  
}
