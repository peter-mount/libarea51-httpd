/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/webserver.h>

int sendResponse(struct MHD_Connection *connection, int status, struct MHD_Response *response) {
    if (response) {
        int ret = MHD_queue_response(connection, status, response);
        MHD_destroy_response(response);
        return ret;
    } else {

        return MHD_NO;
    }
}
