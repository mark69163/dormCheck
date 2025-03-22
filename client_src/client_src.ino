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

  //wifi manager setup
  WiFiManager wm;
  //wm.resetSettings(); //forgets previously connected network
  if (!wm.autoConnect("dormcheckAP", "password")) {
        //Serial.println("Failed to start as AP.");
    }

  //OTA upadte setup
  ArduinoOTA.setHostname("dormCheck_node_1");
  ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();

  // pheripheral setup
  init_buzzer();
  init_led();
  init_relay();
  init_door_sensor();
  init_nfc_reader();

  //mute_buzzer(true);
  //disable_led(true);
  //disable_relay(true);
}

void loop(){
  ArduinoOTA.handle();

  if(is_card_present()){
    toggle_relay(ACCEPT);
    display_led(ACCEPT);
    play_tune(ACCEPT);
  }
  else{
    toggle_relay(DECLINE);
    pixels.clear();
    pixels.show();
  }

}