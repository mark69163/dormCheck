#include "led.h"
#include "config.h"
#include "settings.h"
#include <Arduino.h>

void init_led() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void display_led(States pattern) {
  static unsigned long previousMillis = 0;
  const unsigned long interval = 100;  // This defines how fast the LEDs change (in milliseconds)
  static int pixelIndex = 0;
  unsigned long currentMillis = millis();

  if (is_led_disabled()) {
    return;
  }

  switch (pattern) {
    case STANDBY:
        for (int i = 0; i <= NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 5));  
        }
        pixels.show();
    break;

    case PROCESSING:
      pixels.clear();
      pixels.show();
      for (int i = 0; i <= NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 5));  
        pixels.show();
        delay(100);
      }
      /*
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        pixels.setPixelColor(pixelIndex, pixels.Color(0, 0, 5));  // Light up the next LED
        pixels.show();

        pixelIndex++;
        if (pixelIndex >= NUMPIXELS) {
          pixelIndex = 0;  // Reset to first LED after all have been lit
          pixels.clear();  // Clear all LEDs before updating
        }
      }
      */
      break;

    case ACCEPT:
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 5, 0));  
        }
        pixels.show();
      break;
    case DECLINE:
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(5, 0, 0));  
        }
        pixels.show();
      break;
    case TEST:
      break;

      default:
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(5, 0, 0));  
        }
        pixels.show();
      break;
  }
}