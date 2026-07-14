// Definisi Pin Arduino ke Segment (Berdasarkan urutan kabel di gambar)
const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

// Jika menggunakan Common Anode (seperti di gambar, pin tengah ke 5V):
// Logika LOW = Nyala, HIGH = Mati
int nyala = LOW;
int mati = HIGH;

void setup() {
  // Set semua pin sebagai OUTPUT
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
}

void tampilkanAngka(int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(segmentA, a);
  digitalWrite(segmentB, b);
  digitalWrite(segmentC, c);
  digitalWrite(segmentD, d);
  digitalWrite(segmentE, e);
  digitalWrite(segmentF, f);
  digitalWrite(segmentG, g);
}

void loop() {
  // Tampilkan angka 1
  tampilkanAngka(mati, nyala, nyala, mati, mati, mati, mati);
  delay(1000);

  // Tampilkan angka 3
  tampilkanAngka(nyala, nyala, nyala, nyala, mati, mati, nyala);
  delay(1000);

  // Tampilkan angka 2
  tampilkanAngka(nyala, nyala, mati, nyala, nyala, mati, nyala);
  delay(1000);

  // Tampilkan angka 9
  tampilkanAngka(nyala, nyala, nyala, nyala, mati, nyala, nyala);
  delay(1000);

  // Jeda sebentar sebelum mengulang (semua mati)
  tampilkanAngka(mati, mati, mati, mati, mati, mati, mati);
  delay(2000); 
}
