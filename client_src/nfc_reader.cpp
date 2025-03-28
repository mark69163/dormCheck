#include "config.h"
#include "nfc_reader.h"

void init_nfc_reader(){
    SPI.begin();
    rfid.PCD_Init();
}

bool is_card_present(){
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())return true;
  else return false;
}

String read_nfc_card(){
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    rfid.PICC_HaltA();
    return uid;
}
