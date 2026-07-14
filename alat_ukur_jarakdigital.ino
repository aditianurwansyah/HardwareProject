#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD (Alamat 0x27, 16 kolom, 2 baris)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 5;
const int echoPin = 18;
const int buzzerPin = 19;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jarak Monitor:");
}

void loop() {
  // Trigger sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Hitung durasi pantulan
  long duration = pulseIn(echoPin, HIGH);
  // Konversi ke CM (Kecepatan suara / 2)
  int distance = duration * 0.034 / 2;

  // Tampilkan di LCD
  lcd.setCursor(0, 1);
  lcd.print("Jarak: ");
  lcd.print(distance);
  lcd.print(" cm   "); // Spasi tambahan untuk hapus sisa angka sebelumnya

  // Tampilkan di Serial Monitor (Syarat monitor)
  Serial.print("Data Jarak: ");
  Serial.println(distance);

  // Logika Buzzer (Berbunyi jika jarak < 20cm)
  if (distance < 20 && distance > 0) {
    digitalWrite(buzzerPin, HIGH);
    delay(distance * 5); // Semakin dekat, jeda bunyi semakin pendek (cepat)
    digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);
  }else{
    noTone(buzzerPin);
  }

  delay(100);
}
