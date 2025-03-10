#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_NeoPixel.h>

#define BUZZER_PIN    5   //D1
#define RELAY_PIN     4   //D2
#define NEOPIXEL_PIN  15  //D8
#define NUMPIXELS     8   //number of RGB LEDs 

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

/*
  MFRC 522 NFC card reader

  SPI wiring

  RST	GPIO 0 (D3)
  MISO	GPIO 12 (D6)
  SCK	GPIO 14 (D5)
  MOSI	GPIO 13 (D7)
*/

#define RFID_CS_PIN   2   //D4

#ifndef STASSID
#define STASSID   "Mark-wifi-2.4G"
#define STAPSK    "MilkaCsoki22"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

void ledTest();
void testBuzzer();
void relayTest();

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN,OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname("dormCheck_node_1");
  ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();

  pixels.begin();
  pixels.clear();
  pixels.show();
  
  //digitalWrite(RELAY_PIN,HIGH);
  digitalWrite(BUZZER_PIN,LOW);
}

void loop() {
  ArduinoOTA.handle();
  //ledTest();
  //testBuzzer();
  relayTest();
}

//////////////////// NEOPIXEL ////////////////////////////


void ledTest(){
  static unsigned long previousMillis = 0;
  const unsigned long interval = 150;
  static int pixelIndex = 0;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    pixels.clear(); // Clear all LEDs before updating

    for (int i = 0; i <= pixelIndex; i++) { 
      pixels.setPixelColor(i, pixels.Color(0, 0, 5)); // Light up LEDs progressively
    }
    pixels.show();

    pixelIndex++;
    if (pixelIndex > NUMPIXELS) {
      pixelIndex = 0; // Reset after all LEDs have been lit
      pixels.clear(); // Clear all LEDs before updating
      pixels.show();
    }
  }
}

//////////////////// BUZZER ////////////////////////////

void testBuzzer() {
  static unsigned long previousMillis = 0;
  const unsigned long interval = 500;
  static bool buzzerState = false;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    buzzerState = !buzzerState;
    digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);
  }
}

//////////////////// RELAY ////////////////////////////
void relayTest(){
  static unsigned long previousMillis = 0;
  const unsigned long interval = 500;
  static bool relayState = false;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  }
}