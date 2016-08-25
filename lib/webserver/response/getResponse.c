/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/log.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

/**
 * Returns the current value of reponse atomically
 * @param server WEBSERVER
 * @param response Pointer to the pointer to get
 * @return The value at response at the time of the call, NULL if not able to get it
 */
struct MHD_Response *getResponse(WEBSERVER *webserver, const char *url) {
    struct MHD_Response *ret = NULL;
    webserver_lock(webserver);
    ret = (struct MHD_Response *) hashmapGet(webserver->responseHandlers, (void *) url);
    webserver_unlock(webserver);
    return ret;
}
