#include "config.h"
#include "settings.h"
#include "buzzer.h"
#include "led.h"
#include "relay.h"
#include "door_sensor.h"
#include "nfc_reader.h"

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
MFRC522 rfid(RFID_SS_PIN, RST_PIN);

void setup(){
  //Serial.begin(115200);
  init_buzzer();
  init_led();
  init_relay();
  init_door_sensor();
  init_nfc_reader();

  mute_buzzer(true);
  disable_led(true);
  disable_relay(true);
}

void loop(){

}