#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(2, 3);   // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED pins
#define BLUE_LED 4
#define GREEN_LED 5
#define RED_LED 6

// Flex sensor pins
#define FLEX1 A0
#define FLEX2 A1
#define FLEX3 A2
#define FLEX4 A3

int f1 = 0, f2 = 0, f3 = 0, f4 = 0;

// Set these from your real readings
int thresh1 = 120;
int thresh2 = 190;
int thresh3 = 120;
int thresh4 = 850;

String lastGesture = "";

void showMessage(String id, String line1, String line2, String btMsg, int b, int g, int r) {
  if (lastGesture != id) {
    digitalWrite(BLUE_LED, b);
    digitalWrite(GREEN_LED, g);
    digitalWrite(RED_LED, r);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);

    mySerial.println(btMsg);
    Serial.println("BT: " + btMsg);

    lastGesture = id;
    delay(2000);
  }
}

void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.begin(9600);
  mySerial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("Smart Hands");

  mySerial.println("Welcome To Smart Hands");
  Serial.println("BT: Welcome To Smart Hands");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Attention Please");
  lcd.setCursor(0, 1);
  lcd.print("...");
}

void loop() {
  f1 = analogRead(FLEX1);
  f2 = analogRead(FLEX2);
  f3 = analogRead(FLEX3);
  f4 = analogRead(FLEX4);

  Serial.print("F1="); Serial.print(f1);
  Serial.print(" F2="); Serial.print(f2);
  Serial.print(" F3="); Serial.print(f3);
  Serial.print(" F4="); Serial.println(f4);

  if (f1 > thresh1) {
    showMessage("G1", "I am requesting", "Help", "I am requesting Help", HIGH, LOW, LOW);
  }
  else if (f2 > thresh2) {
    showMessage("G2", "We are batch 3", "students", "We are batch 3 students", LOW, HIGH, LOW);
  }
  else if (f3 > thresh3) {
    showMessage("G3", "Project:", "Smart Hands", "Project: Smart Hands", LOW, LOW, HIGH);
  }
  else if (f4 > thresh4) {
    showMessage("G4", "Thank You For", "Your Time", "Thank You For Your Time", HIGH, HIGH, LOW);
  }
  else {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);

    if (lastGesture != "IDLE") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Attention Please");
      lcd.setCursor(0, 1);
      lcd.print("...");
      lastGesture = "IDLE";
    }
  }

  delay(200);
}