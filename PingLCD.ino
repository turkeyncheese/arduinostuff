#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 13, 11, 10, 9, 8);
const int pingPin = 7;
const int echoPin = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  long duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  lcd.setCursor(0, 0);
  lcd.print("Inches: ");
  lcd.print(inches);
  lcd.setCursor(0, 1);
  lcd.print("CM: ");
  lcd.print(cm);
  delay(100);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
