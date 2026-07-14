#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD (Alamat I2C biasanya 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int pinLDR = 4;
const int pinVolt = 5;
const int pinCurr = 6;
const int pinRelay = 10;
const int pinBuzzer = 11;

void setup() {
  Serial.begin(115200);
  
  // Setup Pins
  pinMode(pinRelay, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  
  // I2C khusus ESP32-S3 (SDA: 8, SCL: 9)
  Wire.begin(8, 9);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Solar Guardian");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Baca Data Sensor (ADC 12-bit: 0-4095)
  int ldrRaw = analogRead(pinLDR);
  int voltRaw = analogRead(pinVolt);
  int currRaw = analogRead(pinCurr);

  // 2. Konversi ke Nilai Logis
  // Kita asumsikan intensitas cahaya 0-100%
  float sunIntensity = (ldrRaw / 4095.0) * 100.0;
  // Simulasi Tegangan 0-20V dan Arus 0-5A
  float voltage = (voltRaw / 4095.0) * 20.0;
  float current = (currRaw / 4095.0) * 5.0;
  
  // 3. Hitung Daya & Efisiensi
  float powerOut = voltage * current; 
  // Ekspektasi daya maksimal jika 100% matahari adalah 100 Watt
  float expectedPower = sunIntensity; 
  float efficiency = (powerOut / (expectedPower + 0.1)) * 100.0; // +0.1 cegah div by zero

  // 4. Logika Diagnostik
  lcd.setCursor(0, 0);
  lcd.print("P:"); lcd.print(powerOut, 1); lcd.print("W ");
  lcd.print("Sun:"); lcd.print((int)sunIntensity); lcd.print("%");

  lcd.setCursor(0, 1);
  if (sunIntensity > 20.0) { // Hanya cek jika ada matahari
    if (efficiency < 40.0) {
      lcd.print("Status: DIRTY!  ");
      digitalWrite(pinRelay, HIGH); // Nyalakan Pompa Pembersih
      tone(pinBuzzer, 1000, 200);   // Bunyi peringatan
    } else {
      lcd.print("Status: OPTIMAL ");
      digitalWrite(pinRelay, LOW);
      noTone(pinBuzzer);
    }
  } else {
    lcd.print("Status: NIGHT   ");
    digitalWrite(pinRelay, LOW);
  }

  // Debug Serial
  Serial.print("Eff: "); Serial.print(efficiency); Serial.println("%");
  
  delay(1500); 
}
