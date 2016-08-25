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

/**
 * Returns the current value of reponse atomically
 * @param server WEBSERVER
 * @param response Pointer to the pointer to get
 * @return The value at response at the time of the call, NULL if not able to get it
 */
struct MHD_Response *getResponse(const char *url) {
    struct MHD_Response *ret = NULL;
    if (0 != pthread_mutex_lock(&webserver.mutex)) {
        logconsole("Failed to aquire mutex for request");
    } else {
        ret = (struct MHD_Response *) hashmapGet(webserver.responseHandlers, (void *) url);
        pthread_mutex_unlock(&webserver.mutex);
    }
    return ret;
}
