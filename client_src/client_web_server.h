#ifndef CLIENT_WEB_SERVER_H
#define CLIENT_WEB_SERVER_H

/*
void init_web_server();
void handle_logs();
void web_server_log(String message);
*/

void init_web_server();
void handle_logs();
void web_server_log(String message);

void handleRoot();
void handleWiFiUpdate();
void serveSelfDiagnostics();
void serveSettings();

#endif
