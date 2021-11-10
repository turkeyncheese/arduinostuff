#include <SPI.h>
#include <Servo.h>
#include <RFID.h>
#include <LiquidCrystal.h>
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);
String rfidCard;
Servo myservo;
int pos = 0;
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Lock...");
  SPI.begin();
  rfid.init();
  myservo.attach(8);
  pinMode(1, LOW);
  lcd.begin(16,2);
  lcd.print("Scan RFID Card");
}
void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      if (rfidCard == "9 58 86 89") {
        Serial.println("Correct Card: " + rfidCard);
        lcd.clear();
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Welcome Logan");
        delay(1500);
        for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(15);
        }
        delay(5000);
        for (pos = 180; pos >= 0; pos -= 1) { 
        myservo.write(pos);
        delay(15);
        }
        delay(1000);
        lcd.clear();
        lcd.print("Scan RFID Card");
      } else {
        Serial.println("Incorrect Card: " + rfidCard);
        lcd.clear();
        lcd.print("Access Denied");
        pinMode(1, HIGH);
        delay(3000);
        pinMode(1, LOW);
        lcd.clear();
        lcd.print("Scan RFID Card");
      }
    }
    rfid.halt();
  }
}
