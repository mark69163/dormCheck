#include "server_request.h"
#include "config.h"

#include "client_web_server.h"


int http_get_client(String httpRequestData) {
  WiFiClient client;
  HTTPClient http;

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Begin HTTP request
  http.begin(client, httpRequestData);

  int httpCode = http.GET();  // Perform GET request
  String payload = "-2";

  // Return the HTTP status code
  if (httpCode > 0) {
    payload = http.getString();  // Get response payload
  }

  http.end();
  return payload.toInt();  // Default: unexpected response
}