#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servos
Servo inServo;
Servo outServo;

// Ultrasonic pins (UNCHANGED)
int trigIn = 5;
int echoIn = 4;
int trigOut = 3;
int echoOut = 2;

// Servo pins (UNCHANGED)
int inServoPin = 9;
int outServoPin = 6;

// Parking slots
const int TOTAL_SLOTS = 4;
int Slot = TOTAL_SLOTS;

// Distance limit
int distanceLimit = 10;

// Gate timing
unsigned long gateOpenTime = 0;
const unsigned long GATE_OPEN_DURATION = 3000;
bool inGateOpen = false;
bool outGateOpen = false;

// Function to measure distance
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999;

  long distance = duration * 0.034 / 2;
  if (distance < 2 || distance > 400) return 999;

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
  unsigned long currentTime = millis();

  long distIn = getDistance(trigIn, echoIn);
  long distOut = getDistance(trigOut, echoOut);

  // -------- IN GATE --------
  if (distIn < distanceLimit && !inGateOpen && Slot > 0 && !outGateOpen) {
    inGateOpen = true;
    inServo.write(0);
    Slot--;
    gateOpenTime = currentTime;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Car Entering ");
    lcd.setCursor(0, 1);
    lcd.print("Please proceed");
  }

  // -------- OUT GATE --------
  if (distOut < distanceLimit && !outGateOpen && !inGateOpen) {
    outGateOpen = true;
    outServo.write(0);
    Slot++;
    if (Slot > TOTAL_SLOTS) Slot = TOTAL_SLOTS;
    gateOpenTime = currentTime;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Car Exiting  ");
    lcd.setCursor(0, 1);
    lcd.print("Have a nice day");
  }

  // -------- PARKING FULL --------
  if (distIn < distanceLimit && Slot == 0 && !inGateOpen) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   SORRY :(   ");
    lcd.setCursor(0, 1);
    lcd.print(" Parking Full ");
    delay(1500);
    lcd.clear();
  }

  // -------- CLOSE GATES --------
  if ((inGateOpen || outGateOpen) &&
      (currentTime - gateOpenTime >= GATE_OPEN_DURATION)) {

    inServo.write(90);
    outServo.write(90);

    inGateOpen = false;
    outGateOpen = false;

    lcd.clear();
  }

  // -------- IDLE DISPLAY --------
  if (!inGateOpen && !outGateOpen) {
    lcd.setCursor(0, 0);
    lcd.print("   WELCOME!   ");
    lcd.setCursor(0, 1);
    lcd.print("Slots Left: ");
    lcd.print(Slot);
    lcd.print("/");
    lcd.print(TOTAL_SLOTS);
    lcd.print(" ");
  }

  delay(1000);
}
