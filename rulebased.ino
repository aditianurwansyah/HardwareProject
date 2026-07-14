int harga = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(13, OUTPUT);
pinMode(A0, INPUT);
Serial.begin(9600);
}

void loop() {
  harga = analogRead(A0);
  Serial.println(harga); 
  if (harga > 150) {
    // Jika harga > 500, nyalakan LED
    digitalWrite(13, LOW);
    Serial.println(" - LED Mati");
  } else {
    // Jika harga <= 500, matikan LED
    digitalWrite(13, HIGH);
    Serial.println(" - LED Nyala");
  }                     
  delay(100); 
  

}
