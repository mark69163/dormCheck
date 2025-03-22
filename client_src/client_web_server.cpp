#include "config.h"
#include "client_web_server.h"

String logBuffer = "";

void init_web_server() {
    server.on("/logs", handle_logs);
}

void web_server_log(String message) {
    logBuffer += message + "\n";
}

void handle_logs() {
    server.send(200, "text/plain", logBuffer);
}