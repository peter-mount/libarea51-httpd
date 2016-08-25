/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/webserver.h>

/**
 * Handles a 404 for an unsupported url
 * 
 * @param connection
 * @return 
 */
int notFoundHandler(struct MHD_Connection * connection, WEBSERVER_HANDLER *handler) {
    return queueResponse(connection,&webserver.notFoundResponse);
}
