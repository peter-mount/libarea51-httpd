#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

const char *webserver_getRequestMethod(WEBSERVER_REQUEST *r) {
    return r->method;
}
