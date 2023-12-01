#include <Servo.h>
Servo myservo;
int ir1Pin = 12;
int ir2Pin = 11;
int ir3Pin = 10;
int val = 0;
int valA1 = 0;
int valA2 = 0;
int led = 9;

bool servoMotion = false;
unsigned long motionStartTime = 0;

void setup() {
  myservo.attach(8);

  pinMode(ir2Pin, INPUT); 
  pinMode(ir3Pin, INPUT); 
  pinMode(ir1Pin, INPUT); 
  pinMode(led, OUTPUT); 
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  val = digitalRead(ir1Pin);
  valA1 = digitalRead(ir2Pin);
  valA2 = digitalRead(ir3Pin);
  myservo.write(0); //ค่ายิ่งน้อย ปากยิ่งกว้าง
  if (val == 0 || valA1 == 0 || valA2 == 0) {
    // motionStartTime = millis();
    Serial.println("YES");
    servoMotion = true; // Enable servo motion if motion is detected
  } else {
    Serial.println("NO");
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
  digitalWrite(led ,LOW);
  myservo.write(60);
  delay(400);
  myservo.write(0);
  delay(150);
  digitalWrite(led , HIGH);

}