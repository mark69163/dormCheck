#ifndef SETTINGS_H
#define SETTINGS_H

void mute_buzzer(bool mute);
bool is_buzzer_muted();

void disable_led(bool disable);
bool is_led_disabled();

void disable_relay(bool disable);
bool is_relay_disabled();

#endif
