#include "server_request.h"
#include "config.h"

int http_get_client(String httpRequestData) {
  WiFiClient client;
  HTTPClient http;

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Begin HTTP request
  http.begin(client, httpRequestData);

  int httpCode = http.GET();  // Perform GET request

  // Return the HTTP status code
  if (httpCode > 0) {
    String payload = http.getString();  // Get response payload

    // If response is valid (200 OK), handle further logic in main sketch
    if (httpCode == 200) {
      if (payload == "1") {
        http.end();
        return 1;  // Authorized card
      } else if (payload == "0") {
        http.end();
        return 0;  // Unauthorized card
      }
      http.end();
      return -1;  // Unexpected response
    }
  } else {
    // Connection failed
    http.end();
    return -2;
  }

  http.end();
  return -1;  // Default: unexpected response
}

int http_post_client(String httpRequestData) {
  WiFiClient client;
  HTTPClient http;

  // Begin HTTP request
  http.begin(client, serverName);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(httpRequestData);

  if (httpResponseCode > 0) {
    //log("HTTP Response code: " + httpResponseCode);
    if (httpResponseCode == 200) {
      http.end();
      return 1;
    } else {
      http.end();
      return -1;  // unexpected response
    }
  } else {
    http.end();
    return -2;  // connection failed
  }
  http.end();
  return -1;  // Default: unexpected response
}
