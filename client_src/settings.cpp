#include "settings.h"
#include "config.h"

void mute_buzzer(bool mute) {
    buzzerMuted = mute;
}

bool is_buzzer_muted() {
    return buzzerMuted;
}

void disable_led(bool disable){
  ledDisabled = disable;
}

bool is_led_disabled(){
  return ledDisabled;
}

void disable_relay(bool disable){
  relayDisabled = disable;
}

bool is_relay_disabled(){
  return relayDisabled;
}