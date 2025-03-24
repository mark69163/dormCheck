#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>              // Core Arduino functions (implicitly included but good practice)
#include <SPI.h>                  // SPI first because MFRC522 depends on it
#include <MFRC522.h>              // NFC reader (depends on SPI)
#include <WiFiManager.h>          // Manages WiFi (includes ESP8266WiFi internally)
#include <ESP8266WebServer.h>     // Web server for local interactions
#include <ArduinoOTA.h>           // Over-the-air updates
#include <WiFiUdp.h>              // Needed for NTPClient
#include <NTPClient.h>            // NTP time synchronization
#include <ESP8266HTTPClient.h>     // HTTP client (GET/POST)
#include <WiFiClient.h>            // Required by ESP8266HTTPClient
#include <Adafruit_NeoPixel.h>     // LED control

/*
  MFRC 522 NFC card reader

  SPI wiring

  RST	GPIO 0 (D3)
  MISO	GPIO 12 (D6)
  SCK	GPIO 14 (D5)
  MOSI	GPIO 13 (D7)
*/

// Pin Definitions
#define RELAY_PIN 	  	16 	//D0
#define BUZZER_PIN 		  5	  //D1
#define DOOR_SENS_PIN	  4	  //D2

#define NEOPIXEL_PIN 	  15	//D8
#define RFID_SS_PIN 	  2	  //D4
#define RST_PIN 		    0	  //D3

#define NUMPIXELS 		  8	  //number of RGB LEDs
	
// Network & API
#define apiKeyValue     "tPmAT5Ab3j7F9"
#define serverName      "http://192.168.20.1/dormcheck-post-data.php"
#define serverRequest   "http://192.168.20.1/dormcheck-get-data.php"

extern ESP8266WebServer server;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
extern Adafruit_NeoPixel pixels;
extern MFRC522 rfid;

extern bool buzzerMuted;  
extern bool ledDisabled;
extern bool relayDisabled;

typedef enum {
    STANDBY,
    PROCESSING,
    ACCEPT,
    DECLINE,
    UNRECOGNIZED,
    TEST
} States;

extern States state;

#endif
