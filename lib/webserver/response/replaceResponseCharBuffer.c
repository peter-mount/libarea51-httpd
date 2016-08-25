/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/webserver.h>

void replaceResponseCharBuffer(const char *url, CharBuffer *b, const char *contentType) {
    int len;
    void *data = charbuffer_toarray(b, &len);
    replaceResponseArray(url, data, len, contentType);
}
