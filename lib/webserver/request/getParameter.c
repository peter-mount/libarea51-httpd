#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

const char *webserver_getRequestParameter(WEBSERVER_REQUEST *r, const char *arg) {
    return MHD_lookup_connection_value(r->connection, MHD_GET_ARGUMENT_KIND, arg);
}
