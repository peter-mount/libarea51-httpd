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

int webserver_sendResponse(WEBSERVER_REQUEST *request, int status, struct MHD_Response *response) {
    if (response) {
        int ret = MHD_queue_response(request->connection, status, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}
