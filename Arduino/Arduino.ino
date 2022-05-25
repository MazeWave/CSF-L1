/**
CODE NON TESTÉ ET ABSOLUMENT PAS FONCTIONNEL
SERT UNIQUEMENT DE REFERENCE

TODO
- Intégrer la partie LoRa après tests du module MFRC.
**/

#define CFG_EU 1

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

// LoRaWAN end-device
static const u4_t DEVADDR = 0x00000000;
static const PROGMEM u1_t NWKSKEY[16] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u1_t PROGMEM APPSKEY[16] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static uint8_t mydata[30];
static osjob_t sendjob;
const unsigned TX_INTERVAL = 30;

#define echoPin 2
#define trigPin 3

long duration;
int distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

/*
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  rfid.PCD_Init();
  delay(4);
  rfid.PCD_DumpVersionToSerial();
}

void loop()
{
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }

  rfid.PICC_DumpToSerial(&(rfid.uid));
}
*/
