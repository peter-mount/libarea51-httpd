/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/webserver.h>

static int serve(struct MHD_Connection * connection, WEBSERVER_HANDLER *handler, const char *url) {
    struct MHD_Response *response = getResponse(handler->node.name);
    return response ? queueResponse(connection, &response) : MHD_NO;
}

void webserver_add_response_handler(const char *url) {
    webserver_add_handler(url, serve);
}
