#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();


#define del 400
int a1_pin = 5, a2_pin = 18, a3_pin, a4_pin;
int b1_pin, b2_pin, b3_pin, b4_pin;
int c1_pin, c2_pin, c3_pin, c4_pin;

Servo a1, a2, a3, a4;
Servo b1, b2, b3, b4;
Servo c1, c2, c3, c4;



void setup() {
  Serial.begin(9600);
  myServo.begin();
  myServo.setPWMFreq(60);
  delay(10);
  a1.attach(a1_pin);
  a2.attach(a2_pin);
}

void loop() {
  forward();
  
}
int dp[1000][1000];
void forward(){ 
  for(int i = 0; i < 5; i++){
      a1.write(15 * i);
      delay(500);
  }
}

// void forward(){
  

//   a1.write(90);
//   delay(del);
//   a2.write(90);
//   delay(del);
//   a1.write(0);
//   delay(del);
//   a2.write(0);
//   delay(del);
// }
 