#include <Servo.h>
Servo myservo;
int digitalPin = 8;
int avoid1Pin = 3;
int avoid2Pin = 5;
int led = 13;
int val = 0;
int valA1 = 0;
int valA2 = 0;

bool servoMotion = false;
unsigned long motionStartTime = 0;

void setup() {
  myservo.attach(9);

  pinMode(avoid1Pin, INPUT); 
  pinMode(avoid2Pin, INPUT); 
  pinMode(digitalPin, INPUT); 
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  val = digitalRead(digitalPin);
  valA1 = digitalRead(avoid1Pin);
  valA2 = digitalRead(avoid2Pin);
  Serial.print(val);
  Serial.print("   ");
  Serial.print(valA1);
  Serial.print("   ");
  Serial.println(valA2);
  myservo.write(10); //ค่ายิ่งน้อย ปากยิ่งกว้าง
  if (val == 0 || valA1 == 0 || valA2 == 0) {
    motionStartTime = millis();
    // Serial.println("YES");
    servoMotion = true; // Enable servo motion if motion is detected
  } else {
    // Serial.println("NO");
    servoMotion = false; // Disable servo motion if no motion is detected
  }

  if (servoMotion) {
    servoMotionEnabled();
    if(millis() - motionStartTime >= 4000){
      servoMotion = false;
    }else{
    myservo.write(10); 
    }
  }
 
}

void servoMotionEnabled(){
  digital.write(led,HIGH);
  myservo.write(85);
  delay(500);
  myservo.write(10);
  delay(200);
    digital.write(led,HIGH);

}
