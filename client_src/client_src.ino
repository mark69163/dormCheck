#include "config.h"
#include "settings.h"
#include "buzzer.h"
#include "led.h"
#include "relay.h"
#include "door_sensor.h"


Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


void setup(){
  init_buzzer();
  init_led();
  init_relay();
  init_door_sensor();

  mute_buzzer(true);
  disable_led(true);
  //disable_relay(true);
}

void loop(){  
  if(read_door_sensor()){
    toggle_relay(TEST);
  }

  delay(10);
}