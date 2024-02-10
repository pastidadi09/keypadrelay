#include <Keypad.h>

const int ROW_NUM    = 4; // jumlah baris pada keypad
const int COLUMN_NUM = 4; // jumlah kolom pada keypad

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};    // koneksi pin baris pada keypad ke pin Arduino
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // koneksi pin kolom pada keypad ke pin Arduino

const int relayPins[] = {10, 11, 12, 13}; // pin untuk mengontrol empat relay
bool relayStatus[4] = {false, false, false, false}; // array untuk melacak status masing-masing relay

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // relay off saat awal
  }
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    
    // Cek jika tombol yang ditekan adalah '1', '2', '3', atau '4'
    if (key >= '1' && key <= '4') {
      int relayIndex = key - '1'; // Hitung indeks relay berdasarkan tombol yang ditekan

      if (relayStatus[relayIndex]) {
        // Jika relay sedang ON, matikan relay
        digitalWrite(relayPins[relayIndex], LOW);
        relayStatus[relayIndex] = false;
        Serial.println("Relay " + String(relayIndex + 1) + " OFF");
      } else {
        // Jika relay sedang OFF, nyalakan relay
        digitalWrite(relayPins[relayIndex], HIGH);
        relayStatus[relayIndex] = true;
        Serial.println("Relay " + String(relayIndex + 1) + " ON");
      }
      
      delay(500); // Tunda untuk menghindari bounce pada tombol
    }
  }
}
