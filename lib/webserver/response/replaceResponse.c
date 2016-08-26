/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <stdio.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

/**
 * Atomically replaces destResponse with newResponse, disposing the original
 * @param server WEBSERVER
 * @param destResponse Pointer to the pointer to update
 * @param newResponse New response
 */
void webserver_replaceResponse(WEBSERVER *webserver, const char *url, struct MHD_Response *newResponse) {
    webserver_lock(webserver);
    struct MHD_Response *oldResponse = (struct MHD_Response *) hashmapGet(webserver->responseHandlers, (void *) url);
    if (oldResponse)
        MHD_destroy_response(oldResponse);
    hashmapPut(webserver->responseHandlers, (void *) url, newResponse);
    webserver_unlock(webserver);
}

void webserver_setNotFoundResponse(WEBSERVER *webserver, struct MHD_Response *newResponse) {
    webserver_lock(webserver);
    if (webserver->notFoundResponse)
        MHD_destroy_response(webserver->notFoundResponse);
    webserver->notFoundResponse = newResponse;
    webserver_unlock(webserver);
}

void webserver_setErrorResponse(WEBSERVER *webserver, struct MHD_Response *newResponse) {
    webserver_lock(webserver);
    if (webserver->errorResponse)
        MHD_destroy_response(webserver->errorResponse);
    webserver->errorResponse = newResponse;
    webserver_unlock(webserver);
}
