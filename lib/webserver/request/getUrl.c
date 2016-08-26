#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <area51/webserver.h>
#include <area51/string.h>
#include "../webserver-int.h"

// Don't allow any file begining with . to prevent people trying to scan filesystem
static const char *INVALID = "/.";

/*
 * Get the url from the request
 */
const char *webserver_getRequestUrl(WEBSERVER_REQUEST *r) {
    return r->url;
}

/**
 * Validates a url: Not null, starts with '/' and does not contain '/.' which can
 * be used as an attempt to escape out of some directory.
 */
bool webserver_isUrlValid(WEBSERVER_REQUEST *r) {
    char *url = (char *) r -> url;

    return url &&
            url[0] == '/' &&
            findString(url, (char *) INVALID) == NULL;
}