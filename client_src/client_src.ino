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
NTPClient timeClient(ntpUDP);
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
MFRC522 rfid(RFID_SS_PIN, RST_PIN);

float get_temp();
String get_date_timestamp();
String get_time_timestamp();

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

  //mute_buzzer(true);
  //disable_led(true);
  //disable_relay(true);
  display_led(STANDBY);
}

void loop() {
  ArduinoOTA.handle();
  timeClient.update();
  server.handleClient();

  /*
  put program logic here
  */

  if (is_card_present()) {
    String cardID = read_nfc_card();

    String requestURL = String(serverRequest) + "?cardid=" + cardID;
    int payload = http_get_client(requestURL);
    String cevent = "UNKNOWNCARD";

    if (payload == 1) {
      cevent = "AUTHORIZED";
      toggle_relay(ACCEPT);
      display_led(ACCEPT);
      play_tune(ACCEPT);
      web_server_log("UID: " + cardID + " | Date: " + get_date_timestamp() + " | Time: " + get_time_timestamp());
      delay(3000);
    } else if (payload == 0) {
      String cevent = "UNAUTHORIZED";
      toggle_relay(DECLINE);
      display_led(DECLINE);
      play_tune(DECLINE);
      web_server_log("Unauthorized attempt.");
    } else {
      web_server_log("Unexpected response from server.");
    }

    String httpRequestData = "api_key=" + String(apiKeyValue) 
                                        + "&cardid=" + cardID
                                        + "&userid=" + 1 
                                        + "&cevent=" + cevent
                                        + "&check_time=" + get_date_timestamp() + " " + get_time_timestamp() + "";
    
    http_post_client(httpRequestData);
  }

  toggle_relay(DECLINE);
  display_led(STANDBY);
  pixels.show();

}

// helper functions
float get_temp(){
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