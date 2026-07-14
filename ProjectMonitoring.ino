#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledGreen = 6;
const int ledRed = 7;
const int buzzer = 8;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if (!mpu.begin()) {
    lcd.print("MPU Tidak Ada!");
    while (1) yield();
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Sleep Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Menghitung resultan gaya gravitasi (total getaran)
  float totalAcc = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z));
  
  // Ambang batas (threshold) sederhana
  // Normal gravitasi bumi sekitar 9.8 m/s^2
  float movement = abs(totalAcc - 9.8);

  lcd.setCursor(0, 0);
  lcd.print("Mov: ");
  lcd.print(movement);

  lcd.setCursor(0, 1);
  if (movement < 0.15) {
    lcd.print("Stat: Deep Sleep ");
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  } else if (movement >= 0.15 && movement < 1.5) {
    lcd.print("Stat: Light Sleep");
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    lcd.print("Stat: Awake      ");
    digitalWrite(ledRed, HIGH);
    tone(buzzer, 1000, 100); // Bunyi singkat jika ada gerakan besar
  }

  delay(500);
}
