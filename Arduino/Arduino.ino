/**
CODE NON TESTÉ ET ABSOLUMENT PAS FONCTIONNEL
SERT UNIQUEMENT DE REFERENCE

TODO
- Intégrer la partie LoRa après tests du module MFRC.
**/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  // TODO
}

void loop()
{
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte mfblock;
  byte mflen;
  MFRC522::StatusCode mfstatus;

  //-------------------------------------------

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
}
