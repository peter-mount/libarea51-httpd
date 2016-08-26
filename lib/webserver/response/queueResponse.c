/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <pthread.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

/**
 * Queues a response to a connection. This does it atomically so that the response will be queued even if another
 * thread replaces the response, i.e. a new camera image.
 * @param connection
 * @param server
 * @param response
 * @return 
 */
int webserver_queueResponse(WEBSERVER_REQUEST *request, struct MHD_Response **response) {
    int ret;

    webserver_lock(request->webserver);

    if (*response) {
        ret = MHD_queue_response(request->connection, MHD_HTTP_OK, *response);
    } else {
        // Return error if there's no response available, usually before an image is available.
        ret = MHD_queue_response(request->connection, MHD_HTTP_NOT_FOUND, request->webserver->notFoundResponse);
    }

    webserver_unlock(request->webserver);

    return ret;
}
