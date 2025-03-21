#include "buzzer.h"
#include "config.h"
#include "settings.h"

void init_buzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void play_tune(States tune) {

    if (is_buzzer_muted()) {
        return;  // Do nothing if the buzzer is muted
    }

  switch (tune) {
    case ACCEPT:
      tone(BUZZER_PIN, 1000, 250);  // First high note (tü)
      delay(100);                   // Short pause
      tone(BUZZER_PIN, 600, 250);   // Low note (tü)
      delay(100);                   // Short pause
      tone(BUZZER_PIN, 1000, 250);  // First high note again (tü)
      delay(100);                   // Short pause
      tone(BUZZER_PIN, 1500, 250);  // Higher note (rüm)
      delay(200);                   // Slightly longer pause to end it
      break;
    case DECLINE:
      tone(BUZZER_PIN, 500, 500);
      delay(500);
      tone(BUZZER_PIN, 500, 500);
      break;
    case TEST:
      break;
  }
}
