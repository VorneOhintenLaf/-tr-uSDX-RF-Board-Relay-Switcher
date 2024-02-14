#include <Wire.h>
#include <TCA9555.h>

// TCA9555 Objekt erstellen und Adresse festlegen
TCA9555 tca9555(0x20);

// Pins für Taster definieren
const int TASTER1_PIN = 2;
const int TASTER2_PIN = 3;
const int TASTER3_PIN = 4;
const int TASTER4_PIN = 5;
const int TASTER5_PIN = 6;
const int TASTER6_PIN = 7;

// Pins für Relais auf dem TCA9555 definieren
const uint8_t RELAIS1_PIN = 11;
const uint8_t RELAIS2_PIN = 10;
const uint8_t RELAIS3_PIN = 12;
const uint8_t RELAIS4_PIN = 9;
const uint8_t RELAIS5_PIN = 13;

// Funktionen vorab deklarieren
void turnRelayOn(uint8_t relayPin);
void turnRelayOff(uint8_t relayPin);
void turnRelayIDLE(uint8_t relayPin); 
void turnAllRelaysOff();

void setup() {
  // Initialisierung von I2C
  Wire.begin();
  
  // Initialisierung des TCA9555
  tca9555.begin();

  tca9555.pinMode1(0,OUTPUT);
  tca9555.pinMode1(11,OUTPUT);
  tca9555.pinMode1(10,OUTPUT);
  tca9555.pinMode1(12,OUTPUT);
  tca9555.pinMode1(9,OUTPUT);
  tca9555.pinMode1(13,OUTPUT);

  // Serielle starten
  Serial.begin(9600);
  
  // Pull-up Widerstände für Taster aktivieren
  pinMode(TASTER1_PIN, INPUT_PULLUP);
  pinMode(TASTER2_PIN, INPUT_PULLUP);
  pinMode(TASTER3_PIN, INPUT_PULLUP);
  pinMode(TASTER4_PIN, INPUT_PULLUP);
  pinMode(TASTER5_PIN, INPUT_PULLUP);
  pinMode(TASTER6_PIN, INPUT_PULLUP);

  // Alle Relais ausschalten
  turnAllRelaysOff();
}

void loop() {
  // Wenn Taster 1 gedrückt wird, schalte Relais 1 ein und dann wieder aus
  if (debounce(TASTER1_PIN) == LOW) {
    turnAllRelaysOff();
    delay(50);
    turnRelayOn(RELAIS1_PIN);
    delay(1000);
    turnRelayIDLE(RELAIS1_PIN);
    Serial.print(1);
  }
  
  // Wenn Taster 2 gedrückt wird, schalte Relais 2 ein und dann wieder aus
  if (debounce(TASTER2_PIN) == LOW) {
    turnAllRelaysOff();
    delay(50);
    turnRelayOn(RELAIS2_PIN);
    delay(1000);
    turnRelayIDLE(RELAIS2_PIN);
    Serial.print(2);
  }
  
  // Wenn Taster 3 gedrückt wird, schalte Relais 3 ein und dann wieder aus
  if (debounce(TASTER3_PIN) == LOW) {
    turnAllRelaysOff();
    delay(50);
    turnRelayOn(RELAIS3_PIN);
    delay(1000);
    turnRelayIDLE(RELAIS3_PIN);
    Serial.print(3);
  }
  
  // Wenn Taster 4 gedrückt wird, schalte Relais 4 ein und dann wieder aus
  if (debounce(TASTER4_PIN) == LOW) {
    turnAllRelaysOff();
    delay(50);
    turnRelayOn(RELAIS4_PIN);
    delay(1000);
    turnRelayIDLE(RELAIS4_PIN);
    Serial.print(4);
  }
  
  // Wenn Taster 5 gedrückt wird, schalte Relais 5 ein und dann wieder aus
  if (debounce(TASTER5_PIN) == LOW) {
    turnAllRelaysOff();
    delay(50);
    turnRelayOn(RELAIS5_PIN);
    delay(1000);
    turnRelayIDLE(RELAIS5_PIN);
    Serial.print(5);
  }
  
  // Wenn Taster 6 gedrückt wird, schalte alle Relais aus
  if (debounce(TASTER6_PIN) == LOW) {
    turnAllRelaysOff();
    delay(1000);
    Serial.print(6);
  }
}

// Funktion, um ein Relais einzuschalten
void turnRelayOn(uint8_t relayPin) {
  // P00 auf Low setzen
  tca9555.write1(0, LOW);
  // Setze den entsprechenden Ausgang des TCA9555 auf High
  tca9555.write1(relayPin, HIGH);
}

// Funktion, um ein Relais auszuschalten
void turnRelayOff(uint8_t relayPin) {
  // Setze den entsprechenden Ausgang des TCA9555 auf Low
  tca9555.write1(relayPin, LOW);
  // P00 auf High setzen
  tca9555.write1(0, HIGH);
}

// Funktion, um ein Relais in den Ruhezustand zu versetzen
void turnRelayIDLE(uint8_t relayPin) {
  // Setze den entsprechenden Ausgang des TCA9555 auf Low
  tca9555.write1(relayPin, LOW);
  // P00 auf Low setzen
  tca9555.write1(0, LOW);
}

// Funktion, um alle Relais auszuschalten
void turnAllRelaysOff() {
  // Setze alle Relaisausgänge auf Low
  tca9555.write1(RELAIS1_PIN, LOW);
  tca9555.write1(RELAIS2_PIN, LOW);
  tca9555.write1(RELAIS3_PIN, LOW);
  tca9555.write1(RELAIS4_PIN, LOW);
  tca9555.write1(RELAIS5_PIN, LOW);
  // P00 auf High setzen
  tca9555.write1(0, HIGH);
}

// Funktion zur Entprellung der Taster
int debounce(int buttonPin) {
  int currentState = digitalRead(buttonPin);
  delay(10);
  int newState = digitalRead(buttonPin);
  if (currentState == newState) {
    return currentState;
  }
  return -1;
}
