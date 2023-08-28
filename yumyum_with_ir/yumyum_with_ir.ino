#include <Servo.h>
Servo myservo;
int digitalPin = 8;
int val = 0;

bool servoMotion = false;
unsigned long motionStartTime = 0;

void setup() {
  myservo.attach(9);
  pinMode(digitalPin, INPUT); 
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  val = digitalRead(digitalPin);
  myservo.write(10); //ค่ายิ่งน้อย ปากยิ่งกว้าง
  if (val == 0) {
    motionStartTime = millis();
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
  myservo.write(85);
  delay(500);
  myservo.write(10);
  delay(200);
}
