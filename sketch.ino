#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
#define MQ3_PIN 34
#define BUTTON_PIN 27
#define BUZZER_PIN 25
#define LED_PIN 26
#define RELAY_PIN 33

void setup() {
  Serial.begin(115200);

  pinMode(MQ3_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Smart Helmet");
  delay(2000);
  lcd.clear();

  digitalWrite(RELAY_PIN, HIGH); // Engine ON initially
}

void loop() {

  int alcoholValue = analogRead(MQ3_PIN);
  int accidentState = digitalRead(BUTTON_PIN);

  Serial.print("Alcohol: ");
  Serial.println(alcoholValue);

  lcd.clear();

  // 🔴 Alcohol Detected
  if (alcoholValue > 2000) {
    lcd.setCursor(0,0);
    lcd.print("Alcohol Detected");
    lcd.setCursor(0,1);
    lcd.print("Engine OFF");

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW); // OFF
  }

  // 🔴 Accident Detected
  else if (accidentState == LOW) {
    lcd.setCursor(0,0);
    lcd.print("Accident!");
    lcd.setCursor(0,1);
    lcd.print("Engine OFF");

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW); // OFF
  }

  // 🟢 Safe Condition
  else {
    lcd.setCursor(0,0);
    lcd.print("Helmet Safe");
    lcd.setCursor(0,1);
    lcd.print("Engine ON");

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH); // ON
  }

  delay(1000);
}