#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H

#include "config.h"

void http_post_client(String httpRequestData);
int  http_get_client(String httpRequestData);

#endif