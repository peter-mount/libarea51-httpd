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

/**
 * Handles a 404 for an unsupported url
 * 
 * @param connection
 * @return 
 */
int notFoundHandler(WEBSERVER_REQUEST *request) {
    return queueResponse(request, &request->webserver->notFoundResponse);
}
