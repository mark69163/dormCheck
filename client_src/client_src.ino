#include "config.h"
#include "settings.h"
#include "buzzer.h"
#include "led.h"
#include "relay.h"
#include "door_sensor.h"
#include "nfc_reader.h"
#include "client_web_server.h"
#include "server_request.h"

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 3600);
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
MFRC522 rfid(RFID_SS_PIN, RST_PIN);

States state = STANDBY;
String cardID = "";
String cevent = "";

unsigned long actualTimeout = 0;

float get_temp();
String get_date_timestamp();
String get_time_timestamp();
void handle_evenet();

void setup() {
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

  init_web_server();
  server.begin();

  timeClient.begin();

  // pheripheral setup
  init_buzzer();
  init_led();
  init_relay();
  init_door_sensor();
  init_nfc_reader();

  display_led(STANDBY);
  //web_server_log("Dormcheck Clinet Node Successfully Booted.");
}

void loop() {
  String requestURL = "";
  int authorizationResponse = 0;

  switch (state) {
    case STANDBY:
      ArduinoOTA.handle();
      timeClient.update();
      server.handleClient();

      if (is_card_present()) {
        state = PROCESSING;
      }
      break;

    case PROCESSING:
      cardID = read_nfc_card();

      requestURL = String(serverRequest) + "?cardid=" + cardID;
      authorizationResponse = http_get_client(requestURL);

      if (authorizationResponse == 1) {
        cevent = "AUTHORIZED";
        actualTimeout = millis();
        state = ACCEPT;
      } else if (authorizationResponse == 0) {
        cevent = "UNAUTHORIZED";
        state = DECLINE;
      } else {
        web_server_log("Unexpected response from server.");
        state = DECLINE;
      }

      display_led(state);
      play_tune(state);

      break;

    case ACCEPT:
      //mute_buzzer(true);
      if (read_door_sensor() || (millis()-actualTimeout>DOOR_TIMEOUT)) {
        web_server_log("UID: " + cardID + " | Event: " + cevent + " |  Date: " + get_date_timestamp() + " | Time: " + get_time_timestamp());
        state = STANDBY;
      }
      break;

    // ACCEPT, DECLINE
    default:
      web_server_log("UID: " + cardID + " | Event: " + cevent + " |  Date: " + get_date_timestamp() + " | Time: " + get_time_timestamp());
      state = STANDBY;
      break;
  };

  toggle_relay(state);
  display_led(state);

}


// helper functions

float get_temp() {
  int reading = analogRead(A0);
  // Convert to voltage (ESP8266 ADC reads 0-1V mapped to 0-1024)
  float voltage = reading * (3.3 / 1024.0);
  // Convert to temperature
  float temperatureC = (voltage - 0.5) * 100.0;

  return temperatureC;
}


String get_date_timestamp() {
  String formattedDateTime = timeClient.getFormattedDate();
  int splitT = formattedDateTime.indexOf("T");
  String dateStamp = formattedDateTime.substring(0, splitT);
  return dateStamp;
}

String get_time_timestamp() {
  String formattedDateTime = timeClient.getFormattedDate();
  int splitT = formattedDateTime.indexOf("T");
  String timeStamp = formattedDateTime.substring(splitT + 1, formattedDateTime.length() - 1);
  return timeStamp;
}