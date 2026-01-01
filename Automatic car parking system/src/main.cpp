#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 
#include <Wire.h> 

#define IN_ECHO_PIN 2
#define IN_TRIG_PIN 3

#define OUT_ECHO_PIN 5
#define OUT_TRIG_PIN 4

int outServoPin =9;
int inServoPin =6;

Servo outServo; 
Servo inServo;

LiquidCrystal_I2C lcd(0x27,16,2);   

void setup(){

  outServo.attach(outServoPin); 
  inServo.attach(inServoPin);

  pinMode(IN_ECHO_PIN, INPUT);
  pinMode(IN_TRIG_PIN,OUTPUT);

  pinMode(OUT_ECHO_PIN, INPUT);
  pinMode(OUT_TRIG_PIN,OUTPUT);

}

void loop(){

}