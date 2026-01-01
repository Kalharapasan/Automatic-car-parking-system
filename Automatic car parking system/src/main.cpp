#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servos
Servo inServo;
Servo outServo;

// Ultrasonic pins
int trigIn = 2;
int echoIn = 3;

int trigOut = 4;
int echoOut = 5;

// Servo pins
int inServoPin = 6;
int outServoPin = 7;

// Parking slots
int Slot = 4;   // TOTAL SLOTS

int flagIn = 0;
int flagOut = 0;

// Distance threshold (cm)
int distanceLimit = 10;

// Function to measure distance
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  return distance;
}

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(trigIn, OUTPUT);
  pinMode(echoIn, INPUT);

  pinMode(trigOut, OUTPUT);
  pinMode(echoOut, INPUT);

  inServo.attach(inServoPin);
  outServo.attach(outServoPin);

  // Close gates
  inServo.write(90);
  outServo.write(90);

  lcd.setCursor(0, 0);
  lcd.print("  ARDUINO CAR  ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYS ");
  delay(2000);
  lcd.clear();
}

void loop() {

  long distIn = getDistance(trigIn, echoIn);
  long distOut = getDistance(trigOut, echoOut);

  // -------- IN GATE --------
  if (distIn < distanceLimit && flagIn == 0) {
    if (Slot > 0) {
      flagIn = 1;
      if (flagOut == 0) {
        inServo.write(0);   // Open gate
        Slot--;
      }
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   SORRY :(   ");
      lcd.setCursor(0, 1);
      lcd.print(" Parking Full ");
      delay(2000);
      lcd.clear();
    }
  }

  // -------- OUT GATE --------
  if (distOut < distanceLimit && flagOut == 0) {
    flagOut = 1;
    if (flagIn == 0) {
      outServo.write(0);  // Open gate
      Slot++;
    }
  }

  // -------- RESET --------
  if (flagIn == 1 && flagOut == 1) {
    delay(1000);
    inServo.write(90);    // Close gates
    outServo.write(90);
    flagIn = 0;
    flagOut = 0;
  }

  // -------- LCD DISPLAY --------
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME!   ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
  lcd.print("  ");

  delay(1000);
}
