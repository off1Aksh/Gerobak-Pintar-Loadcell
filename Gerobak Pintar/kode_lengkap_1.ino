#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int RELAY_IN1 = 5;
const int RELAY_IN2 = 6;
const int RELAY_IN3 = 7;

float angka_kalibrasi = -4986.70;

HX711 scale;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  
  pinMode(RELAY_IN1, OUTPUT);
  pinMode(RELAY_IN2, OUTPUT);
  pinMode(RELAY_IN3, OUTPUT);

  digitalWrite(RELAY_IN1, LOW);
  digitalWrite(RELAY_IN2, LOW);
  digitalWrite(RELAY_IN3, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DENITECH");
  delay(2000);
  lcd.clear();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(angka_kalibrasi);
  scale.set_offset(-533379);

  delay(500);
}

void loop() {
  if (scale.is_ready()) {
    float weight = scale.get_units(15);
    
    if (weight < 0) {
      weight = 0.0;
    }

    Serial.print("Berat: ");
    Serial.print(weight);
    Serial.println(" Kg");

    lcd.setCursor(0, 0);
    lcd.print("Berat: ");
    lcd.print(weight, 1);
    lcd.print(" Kg    ");

    lcd.setCursor(0, 1);

    if (weight < 150.0) {
      digitalWrite(RELAY_IN1, LOW);
      digitalWrite(RELAY_IN2, HIGH);
      digitalWrite(RELAY_IN3, HIGH);
      lcd.print("Status: AMAN   ");
    } 
    else if (weight >= 150.0 && weight <= 350.0) {
      digitalWrite(RELAY_IN1, HIGH);
      digitalWrite(RELAY_IN2, LOW);
      digitalWrite(RELAY_IN3, HIGH);
      lcd.print("Status: WASPADA");
    } 
    else if (weight > 350.0) {
      digitalWrite(RELAY_IN1, HIGH);
      digitalWrite(RELAY_IN2, HIGH);
      digitalWrite(RELAY_IN3, LOW);
      lcd.print("Status: BERAT! ");
    }
  } else {
    Serial.println("HX711 Error");
    lcd.setCursor(0, 0);
    lcd.print("HX711 Error    ");
    lcd.setCursor(0, 1);
    lcd.print("Cek Kabel!     ");
  }
  
  delay(1000);
}