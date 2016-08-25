/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

static int serve(WEBSERVER_REQUEST *request) {
    struct MHD_Response *response = getResponse(request->webserver, request->handler->node.name);
    return response ? queueResponse(request, &response) : MHD_NO;
}

void webserver_add_response_handler(WEBSERVER *webserver, const char *url) {
    webserver_add_handler(webserver, url, serve, NULL);
}
