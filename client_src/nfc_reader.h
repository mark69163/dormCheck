#ifndef NFC_READER_H
#define NFC_READER_H

#include "config.h"

void init_nfc_reader();
bool is_card_present();
String read_nfc_card();

#endif