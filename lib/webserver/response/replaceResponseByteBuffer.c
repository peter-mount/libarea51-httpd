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

void replaceResponseByteBuffer(WEBSERVER *webserver, const char *url, struct bytebuffer *b, const char *contentType) {
    int len;
    void *data = bytebuffer_toarray(b, &len);
    replaceResponseArray(webserver, url, data, len, contentType);
}
