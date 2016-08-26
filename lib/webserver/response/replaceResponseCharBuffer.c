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

void webserver_replaceResponseCharBuffer(WEBSERVER *webserver, const char *url, CharBuffer *b, const char *contentType) {
    int len;
    void *data = charbuffer_toarray(b, &len);
    webserver_replaceResponseArray(webserver, url, data, len, contentType);
}
