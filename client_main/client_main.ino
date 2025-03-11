#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_NeoPixel.h>
#include <NTPClient.h>
#include <ESP8266WebServer.h>

#include <SPI.h>
#include <MFRC522.h>

#define RELAY_PIN     16  //D0 (was D2)
#define BUZZER_PIN    5   //D1
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

#define RFID_SS_PIN   2   //D4
#define RST_PIN       0   //D3 

MFRC522 rfid(RFID_SS_PIN, RST_PIN);  // Create MFRC522 instance


#ifndef STASSID
#define STASSID   "Mark-wifi-2.4G"
#define STAPSK    "MilkaCsoki22"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

ESP8266WebServer server(80);
String logBuffer = "";

void log(String message) {
  logBuffer += message + "\n";  // Store logs in a buffer
  //Serial.println(message);  // Print to Serial too (if USB is connected)
}

void handleLogs() {
  server.send(200, "text/plain", logBuffer);
}

void ledTest();
void testBuzzer();
void relayTest();

void setup() {
  SPI.begin();			// Init SPI bus
  rfid.PCD_Init();		// Init MFRC522
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN,OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  log("Booting...");
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname("dormCheck_node_1");
  ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();

  timeClient.begin();

  log("\nConnected to WiFi!");

  server.on("/logs", handleLogs);
  server.begin();

  pixels.begin();
  pixels.clear();
  pixels.show();
  
  digitalWrite(RELAY_PIN,HIGH);
  digitalWrite(BUZZER_PIN,LOW);
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  timeClient.update();
  
  String formattedDateTime = timeClient.getFormattedDate();
  int splitT = formattedDateTime.indexOf("T");
  String dateStamp = formattedDateTime.substring(0, splitT);
  String timeStamp = formattedDateTime.substring(splitT + 1, formattedDateTime.length() - 1);
  
  //log("NTP Date: " + dateStamp + " Time: " + timeStamp);
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    log("UID: " + uid + " | Date: " + dateStamp + " | Time: " + timeStamp);
    rfid.PICC_HaltA();
  }
  
  //ledTest();
  //testBuzzer();
  //relayTest();
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
  static bool relayState = false;
  relayState = !relayState;
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  delay(1000);
}